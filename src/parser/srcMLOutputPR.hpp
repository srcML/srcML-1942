/**
 * @file srcMLOutputPR.hpp
 *
 * @copyright Copyright (C) 2005-2014 SDML (www.srcML.org)
 *
 * This file is part of the srcML Toolkit.
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 *  Declaration of process pointer table for srcMLTranslatorOutput.
 */

#include "srcMLParserTokenTypesMacro.hpp"

/**
 * Anonymous enum for process callback positions.
 */
enum {
    PROCESSTOKEN,
    PROCESSUNIT,
    PROCESSTEXT,
    PROCESSBLOCKCOMMENTSTART,
    PROCESSJAVADOCCOMMENTSTART,
    PROCESSDOXYGENCOMMENTSTART,
    PROCESSLINEDOXYGENCOMMENTSTART,
    PROCESSENDBLOCKTOKEN,
    PROCESSLINECOMMENTSTART,
    PROCESSENDLINETOKEN,
#if DEBUG
    PROCESSMARKER,
#endif
    PROCESSACCESS,
    PROCESSSTRING,
    PROCESSCHAR,
    PROCESSLITERAL,
    PROCESSBOOLEAN,
    PROCESSNULL,
    PROCESSCOMPLEX,
    PROCESSINTERFACE,
    PROCESSESCAPE,
    PROCESSTYPEPREV,
    PROCESSSTATICASSERT
};

/** for conversion of process numbers to callbacks */
srcMLOutput::PROCESS_PTR srcMLOutput::num2process[] = {
    &srcMLOutput::processToken,
    &srcMLOutput::processUnit,
    &srcMLOutput::processText,
    &srcMLOutput::processBlockCommentStart,
    &srcMLOutput::processJavadocCommentStart,
    &srcMLOutput::processDoxygenCommentStart,
    &srcMLOutput::processLineDoxygenCommentStart,
    &srcMLOutput::processEndBlockToken,
    &srcMLOutput::processLineCommentStart,
    &srcMLOutput::processEndLineToken,
#if DEBUG
    &srcMLOutput::processMarker,
#endif
    &srcMLOutput::processAccess,
    &srcMLOutput::processString,
    &srcMLOutput::processChar,
    &srcMLOutput::processLiteral,
    &srcMLOutput::processBoolean,
    &srcMLOutput::processNull,
    &srcMLOutput::processComplex,
    &srcMLOutput::processInterface,
    &srcMLOutput::processEscape,
    &srcMLOutput::processTypePrevious,
    &srcMLOutput::processStaticAssert
};

/** element map call name */
#define ELEMENT_MAP_CALL_NAME element_process

/** element map first type */
#define ELEMENT_MAP_FIRST_TYPE int

/** element map second type */
#define ELEMENT_MAP_SECOND_TYPE char

/** element map default operation */
#define ELEMENT_MAP_DEFAULT(s) template <ELEMENT_MAP_FIRST_TYPE n> inline ELEMENT_MAP_SECOND_TYPE \
    ELEMENT_MAP_CALL_NAME() { s }

/** element map call */
#define ELEMENT_MAP_CALL(t) ELEMENT_MAP_CALL_NAME <srcMLParserTokenTypes::t>()

/** element map */
#define ELEMENT_MAP(t, s) template <> inline ELEMENT_MAP_SECOND_TYPE ELEMENT_MAP_CALL(t) /* stuff */ { return s; }

/** map the token types to specific strings */
namespace {

    // base member
    ELEMENT_MAP_DEFAULT(return PROCESSTEXT;)

    ELEMENT_MAP(SUNIT, PROCESSUNIT)
    ELEMENT_MAP(START_ELEMENT_TOKEN, PROCESSTEXT)
    ELEMENT_MAP(COMMENT_START, PROCESSBLOCKCOMMENTSTART)
    ELEMENT_MAP(COMMENT_END, PROCESSENDBLOCKTOKEN)

    ELEMENT_MAP(LINECOMMENT_START, PROCESSLINECOMMENTSTART)
    ELEMENT_MAP(LINECOMMENT_END, PROCESSENDLINETOKEN)
    ELEMENT_MAP(JAVADOC_COMMENT_START, PROCESSJAVADOCCOMMENTSTART)
    ELEMENT_MAP(DOXYGEN_COMMENT_START, PROCESSDOXYGENCOMMENTSTART)
    ELEMENT_MAP(LINE_DOXYGEN_COMMENT_START, PROCESSLINEDOXYGENCOMMENTSTART)

#if DEBUG
    ELEMENT_MAP(SMARKER, PROCESSMARKER)
#endif
    ELEMENT_MAP(SPUBLIC_ACCESS_DEFAULT, PROCESSACCESS)
    ELEMENT_MAP(SPRIVATE_ACCESS_DEFAULT, PROCESSACCESS)
    ELEMENT_MAP(SPROTECTED_ACCESS_DEFAULT, PROCESSACCESS)
    ELEMENT_MAP(SSTRING, PROCESSSTRING)
    ELEMENT_MAP(SCHAR, PROCESSCHAR)
    ELEMENT_MAP(SLITERAL, PROCESSLITERAL)
    ELEMENT_MAP(SBOOLEAN, PROCESSBOOLEAN)
    ELEMENT_MAP(SNULL, PROCESSNULL)
    ELEMENT_MAP(SCOMPLEX, PROCESSCOMPLEX)
    ELEMENT_MAP(SINTERFACE, PROCESSINTERFACE)
    ELEMENT_MAP(CONTROL_CHAR, PROCESSESCAPE)

    ELEMENT_MAP(SNOP, PROCESSTOKEN)
    ELEMENT_MAP(SOPERATOR, PROCESSTOKEN)
    ELEMENT_MAP(SMODIFIER, PROCESSTOKEN)
    ELEMENT_MAP(SNAME, PROCESSTOKEN)
    ELEMENT_MAP(SONAME, PROCESSTOKEN)
    ELEMENT_MAP(SCNAME, PROCESSTOKEN)
    ELEMENT_MAP(STYPE, PROCESSTOKEN)
    ELEMENT_MAP(STYPEPREV, PROCESSTYPEPREV)
    ELEMENT_MAP(SCONDITION, PROCESSTOKEN)
    ELEMENT_MAP(SBLOCK, PROCESSTOKEN)
    ELEMENT_MAP(SINDEX, PROCESSTOKEN)
    ELEMENT_MAP(SDECLTYPE, PROCESSTOKEN)
    ELEMENT_MAP(SATOMIC, PROCESSTOKEN)
    ELEMENT_MAP(SSTATIC_ASSERT_STATEMENT, PROCESSSTATICASSERT)
    ELEMENT_MAP(SGENERIC_SELECTION, PROCESSTOKEN)
    ELEMENT_MAP(SGENERIC_SELECTOR, PROCESSTOKEN)
    ELEMENT_MAP(SGENERIC_ASSOCIATION_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SGENERIC_ASSOCIATION, PROCESSTOKEN)
    ELEMENT_MAP(STYPENAME, PROCESSTOKEN)
    ELEMENT_MAP(STYPEDEF, PROCESSTOKEN)
    ELEMENT_MAP(SENUM, PROCESSTOKEN)
    ELEMENT_MAP(SASM, PROCESSTOKEN)
    ELEMENT_MAP(SMACRO_CALL, PROCESSTOKEN)
    ELEMENT_MAP(SIF_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(STERNARY, PROCESSTOKEN)
    ELEMENT_MAP(STHEN, PROCESSTOKEN)
    ELEMENT_MAP(SELSE, PROCESSTOKEN)
    ELEMENT_MAP(SELSEIF, PROCESSTOKEN)
    ELEMENT_MAP(SWHILE_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SLOCK_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SFIXED_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SCHECKED_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SUNCHECKED_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SUNSAFE_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SDO_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SFOR_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SFOREACH_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SFOR_GROUP, PROCESSTOKEN)
    ELEMENT_MAP(SFOR_INITIALIZATION, PROCESSTOKEN)
    ELEMENT_MAP(SFOR_CONDITION, PROCESSTOKEN)
    ELEMENT_MAP(SFOR_INCREMENT, PROCESSTOKEN)
    ELEMENT_MAP(SEXPRESSION_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SEXPRESSION, PROCESSTOKEN)
    ELEMENT_MAP(SFUNCTION_CALL, PROCESSTOKEN)
    ELEMENT_MAP(SSIZEOF_CALL, PROCESSTOKEN)
    ELEMENT_MAP(SDECLARATION_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SDECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SDECLARATION_INITIALIZATION, PROCESSTOKEN)
    ELEMENT_MAP(SDECLARATION_RANGE, PROCESSTOKEN)
    ELEMENT_MAP(SGOTO_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SCONTINUE_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SBREAK_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SLABEL_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SSWITCH, PROCESSTOKEN)
    ELEMENT_MAP(SCASE, PROCESSTOKEN)
    ELEMENT_MAP(SDEFAULT, PROCESSTOKEN)
    ELEMENT_MAP(SFUNCTION_DEFINITION, PROCESSTOKEN)
    ELEMENT_MAP(SFUNCTION_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SFUNCTION_SPECIFIER, PROCESSTOKEN)
    ELEMENT_MAP(SFUNCTION_LAMBDA, PROCESSTOKEN)
    ELEMENT_MAP(SRETURN_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SPARAMETER_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SPARAMETER, PROCESSTOKEN)
    ELEMENT_MAP(SKRPARAMETER_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SKRPARAMETER, PROCESSTOKEN)
    ELEMENT_MAP(SARGUMENT_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SARGUMENT, PROCESSTOKEN)
    ELEMENT_MAP(SLAMBDA_CAPTURE, PROCESSTOKEN)
    ELEMENT_MAP(SCLASS, PROCESSTOKEN)
    ELEMENT_MAP(SCLASS_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SSTRUCT, PROCESSTOKEN)
    ELEMENT_MAP(SSTRUCT_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SUNION, PROCESSTOKEN)
    ELEMENT_MAP(SUNION_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SDERIVATION_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SPUBLIC_ACCESS, PROCESSTOKEN)
    ELEMENT_MAP(SPRIVATE_ACCESS, PROCESSTOKEN)
    ELEMENT_MAP(SPROTECTED_ACCESS, PROCESSTOKEN)
    ELEMENT_MAP(SSIGNAL_ACCESS, PROCESSTOKEN)
    ELEMENT_MAP(SFOREVER_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SMEMBER_INITIALIZATION_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SCONSTRUCTOR_DEFINITION, PROCESSTOKEN)
    ELEMENT_MAP(SCONSTRUCTOR_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SDESTRUCTOR_DEFINITION, PROCESSTOKEN)
    ELEMENT_MAP(SDESTRUCTOR_DECLARATION, PROCESSTOKEN)
    ELEMENT_MAP(SFRIEND, PROCESSTOKEN)
    ELEMENT_MAP(SCLASS_SPECIFIER, PROCESSTOKEN)
    ELEMENT_MAP(SEXTERN, PROCESSTOKEN)
    ELEMENT_MAP(SNAMESPACE, PROCESSTOKEN)
    ELEMENT_MAP(SUSING_DIRECTIVE, PROCESSTOKEN)
    ELEMENT_MAP(STRY_BLOCK, PROCESSTOKEN)
    ELEMENT_MAP(SCATCH_BLOCK, PROCESSTOKEN)
    ELEMENT_MAP(SFINALLY_BLOCK, PROCESSTOKEN)
    ELEMENT_MAP(STHROW_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(STHROW_SPECIFIER, PROCESSTOKEN)
    ELEMENT_MAP(STHROW_SPECIFIER_JAVA, PROCESSTOKEN)
    ELEMENT_MAP(SNOEXCEPT, PROCESSTOKEN)
    ELEMENT_MAP(STEMPLATE, PROCESSTOKEN)
    ELEMENT_MAP(STEMPLATE_ARGUMENT, PROCESSTOKEN)
    ELEMENT_MAP(STEMPLATE_ARGUMENT_LIST, PROCESSTOKEN)
    ELEMENT_MAP(STEMPLATE_PARAMETER, PROCESSTOKEN)
    ELEMENT_MAP(STEMPLATE_PARAMETER_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_DIRECTIVE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_FILENAME, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_NUMBER, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_ERROR, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_PRAGMA, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_INCLUDE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_DEFINE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_UNDEF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_LINE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_IF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_IFDEF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_IFNDEF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_THEN, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_ELSE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_ELIF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_ENDIF, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_MACRO_DEFN, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_MACRO_VALUE, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_REGION, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_ENDREGION, PROCESSTOKEN)
    ELEMENT_MAP(SCPP_IMPORT, PROCESSTOKEN)
#ifndef DEBUG
    ELEMENT_MAP(SMARKER, PROCESSTOKEN)
#endif
    ELEMENT_MAP(SERROR_PARSE, PROCESSTOKEN)
    ELEMENT_MAP(SERROR_MODE, PROCESSTOKEN)
    ELEMENT_MAP(SIMPLEMENTS, PROCESSTOKEN)
    ELEMENT_MAP(SEXTENDS, PROCESSTOKEN)
    ELEMENT_MAP(SIMPORT, PROCESSTOKEN)
    ELEMENT_MAP(SPACKAGE, PROCESSTOKEN)
    ELEMENT_MAP(SASSERT_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SSYNCHRONIZED_STATEMENT, PROCESSTOKEN)
    ELEMENT_MAP(SATTRIBUTE, PROCESSTOKEN)
    ELEMENT_MAP(STARGET, PROCESSTOKEN)
    ELEMENT_MAP(SLINQ, PROCESSTOKEN)
    ELEMENT_MAP(SFROM, PROCESSTOKEN)
    ELEMENT_MAP(SWHERE, PROCESSTOKEN)
    ELEMENT_MAP(SSELECT, PROCESSTOKEN)
    ELEMENT_MAP(SLET, PROCESSTOKEN)
    ELEMENT_MAP(SORDERBY, PROCESSTOKEN)
    ELEMENT_MAP(SJOIN, PROCESSTOKEN)
    ELEMENT_MAP(SGROUP, PROCESSTOKEN)
    ELEMENT_MAP(SEMPTY, PROCESSTOKEN)
    ELEMENT_MAP(SANNOTATION, PROCESSTOKEN)
    ELEMENT_MAP(SALIGNAS, PROCESSTOKEN)
    ELEMENT_MAP(SALIGNOF, PROCESSTOKEN)

    ELEMENT_MAP(SIN, PROCESSTOKEN)
    ELEMENT_MAP(SON, PROCESSTOKEN)
    ELEMENT_MAP(SEQUALS, PROCESSTOKEN)
    ELEMENT_MAP(SBY, PROCESSTOKEN)
    ELEMENT_MAP(SINTO, PROCESSTOKEN)

    ELEMENT_MAP(SRECEIVER, PROCESSTOKEN)
    ELEMENT_MAP(SMESSAGE, PROCESSTOKEN)
    ELEMENT_MAP(SSELECTOR, PROCESSTOKEN)
    ELEMENT_MAP(SPROTOCOL_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SCATEGORY, PROCESSTOKEN)
    ELEMENT_MAP(SPROTOCOL, PROCESSTOKEN)
    ELEMENT_MAP(SREQUIRED_DEFAULT, PROCESSACCESS)
    ELEMENT_MAP(SREQUIRED, PROCESSTOKEN)
    ELEMENT_MAP(SOPTIONAL, PROCESSTOKEN)
    ELEMENT_MAP(SPROPERTY, PROCESSTOKEN)
    ELEMENT_MAP(SATTRIBUTE_LIST, PROCESSTOKEN)
    ELEMENT_MAP(SSYNTHESIZE, PROCESSTOKEN)
    ELEMENT_MAP(SDYNAMIC, PROCESSTOKEN)
    ELEMENT_MAP(SENCODE, PROCESSTOKEN)
    ELEMENT_MAP(SAUTORELEASEPOOL, PROCESSTOKEN)

}

#undef ELEMENT_MAP_CALL_NAME
#undef ELEMENT_MAP_FIRST_TYPE
#undef ELEMENT_MAP_SECOND_TYPE
#undef ELEMENT_MAP_DEFAULT
#undef ELEMENT_MAP_CALL
#undef ELEMENT_MAP

/** This was moved to fix doxygen problems.  However, may want to move back */
/** boost local macro */
#define BOOST_PP_LOCAL_MACRO(n)   element_process<n>(),

/** boost macro limits */
#define BOOST_PP_LOCAL_LIMITS     (0, TOKEN_END_ELEMENT_TOKEN - 1)

/** the process table */
char srcMLOutput::process_table[] = {

    // fill the array with the prefixes
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO
#undef BOOST_PP_LOCAL_LIMITS

    // fill the array in order of token numbers
/** boost local macro */
#define BOOST_PP_LOCAL_MACRO(n)   element_process<256 + 1 + n>(),

/** boost macro limits */
#define BOOST_PP_LOCAL_LIMITS     (0, TOKEN_END_ELEMENT_TOKEN - 1 - 256)

#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO
#undef BOOST_PP_LOCAL_LIMITS

};
