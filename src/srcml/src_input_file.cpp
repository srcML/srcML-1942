/**
 * @file src_input_file.cpp
 *
 * @copyright Copyright (C) 2014 srcML, LLC. (www.srcML.org)
 *
 * This file is part of the srcml command-line client.
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
 * along with the srcml command-line client; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <src_input_file.hpp>

// Convert input to a ParseRequest and assign request to the processing queue
void src_input_file(ParseQueue& queue,
                    srcml_archive* srcml_arch,
                    const srcml_request_t& srcml_request,
                    const std::string& input_file) {

    // form the parsing request
    ParseRequest* prequest = new ParseRequest;
   
    if (srcml_request.command & SRCML_COMMAND_NOARCHIVE)
        prequest->disk_dir = srcml_request.output_filename;

    if (srcml_request.att_filename)
        prequest->filename = *srcml_request.att_filename;
    else if (input_file != "_")
        prequest->filename = input_file;

    prequest->directory = srcml_request.att_directory;
    prequest->version = srcml_request.att_version;
    prequest->srcml_arch = srcml_arch;
    prequest->language = srcml_request.att_language ? *srcml_request.att_language : "";
    prequest->disk_filename = input_file;

    // Hand request off to the processing queue
    if (prequest->filename) {
        while (prequest->filename->at(0) == '.' || prequest->filename->at(0) == '/') {
            prequest->filename->erase(0,1);
        }
    }

    queue.schedule(prequest);
}
