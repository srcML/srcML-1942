/*
  Properties.hpp

  Copyright (C) 2008-2010  SDML (www.sdml.info)

  This file is part of the srcML translator.

  The srcML translator is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML translator is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML translator; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


*/

#ifndef INCLUDED_PROPERTIES_HPP
#define INCLUDED_PROPERTIES_HPP

void output_info(srcMLUtility& su, int options, int optioncount, int optionorder[]);

#include "ProcessUnit.hpp"
#include "srcmlapps.hpp"

class Properties : public ProcessUnit {
 public :
  Properties(srcMLUtility& su, PROPERTIES_TYPE&nsv, PROPERTIES_TYPE& attrv, int optioncount, int optionorder[], FILE * output = stdout)
    : su(su), nsv(nsv), attrv(attrv), optioncount(optioncount), optionorder(optionorder), output(output)
    {}

  srcMLUtility& su;
  PROPERTIES_TYPE& nsv;
  PROPERTIES_TYPE& attrv;
  int optioncount;
  int* optionorder;
  FILE * output;

 public :

  // extract namespace and attributes from root unit element
  void startRootUnit(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI,
		     int nb_namespaces, const xmlChar** namespaces, int nb_attributes, int nb_defaulted,
		     const xmlChar** attributes) {

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    SAX2ExtractUnitsSrc* pstate = (SAX2ExtractUnitsSrc*) ctxt->_private;

    // collect namespaces from root
    collect_namespaces(nb_namespaces, namespaces, nsv);

    // collect attributes from root
    collect_attributes(nb_attributes, attributes, attrv);

    // encoding is entered as a property
    const char* encoding = (const char*) (ctxt->encoding ? ctxt->encoding : ctxt->input->encoding);

    if (encoding) {
      int i;
      // TODO: Use constant here
      for (i = 0; i < MAXPROPERTIES; ++i)
        if (attrv[i].first == "")
          break;

      attrv[i].first = ".encoding";
      attrv[i].second = encoding;
    }

    // not processing a particular unit, so output
    if (pstate->unit < 1) {

      // output the current data except for the completion of the nested unit count
      output_info(su, *(pstate->poptions), optioncount, optionorder);

      // if visiting all, then do so counting, whether visible or not
      if (pstate->unit == -1) {

	// Keep going, either showing the count or just accumulating it
	ProcessUnit* pcount = isatty(fileno(output)) ? new CountUnits(output) : new ProcessUnit;
	pstate->pprocess = pcount;
      }
    }
  }

  // extract namespace and attributes from root unit element
  void startUnit(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI,
                 int nb_namespaces, const xmlChar** namespaces, int nb_attributes, int nb_defaulted,
                 const xmlChar** attributes) {

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    SAX2ExtractUnitsSrc* pstate = (SAX2ExtractUnitsSrc*) ctxt->_private;

    // collect namespaces
    collect_namespaces(nb_namespaces, namespaces, nsv);

    // collect attributes
    collect_attributes(nb_attributes, attributes, attrv);

    // encoding is entered as a property
    const char* encoding = (const char*) (ctxt->encoding ? ctxt->encoding : ctxt->input->encoding);

    if (encoding) {
      int i;
      for (i = 0; i < MAXPROPERTIES; ++i)
        if (attrv[i].first == "")
          break;

      attrv[i].first = ".encoding";
      attrv[i].second = encoding;
    }

    // output the current data
    output_info(su, *(pstate->poptions), optioncount, optionorder);

    // stop, since normal unit processing would continue on to the contents
    pstate->stopUnit(ctx);
  }
};

#endif
