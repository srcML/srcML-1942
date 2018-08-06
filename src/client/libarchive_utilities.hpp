/**
 * @file libarchive_utilities.hpp
 *
 * @copyright Copyright (C) 2018 srcML, LLC. (www.srcML.org)
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

#ifndef INCLUDED_LIBARCHIVE_UTILTIES_HPP
#define INCLUDED_LIBARCHIVE_UTILTIES_HPP

#include <archive.h>
#include <archive_entry.h>
#include <memory>

// std::unique_ptr deleter functions for libarchive
// usage: std::unique<archive> p(archive_create_new());
// Call p.get() for original pointer
// Will deallocate automatically at end of std::unique_ptr lifetime
namespace std {
    template<>
    struct default_delete<archive> {
        void operator()(archive* ar) { 
            archive_write_close(ar);
            archive_write_free(ar);
        }
    };

    template<>
    struct default_delete<archive_entry> {
        void operator()(archive_entry* e) { 
            archive_entry_free(e);
        }
    };
}

#endif
