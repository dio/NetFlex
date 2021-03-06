// The MIT License (MIT)
//
// Copyright (c) 2015-2017 Simon Ninon <simon.ninon@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <netflex/routing/route.hpp>

namespace netflex {

namespace routing {

//!
//! ctor & dtor
//!
route::route(http::method m, const std::string& path, const route_callback_t& callback)
: m_method(m)
, m_path(path)
, m_callback(callback)
, m_matcher(path) {}


//!
//! matching
//!
bool
route::match(http::request& request) const {
  //! no method matching, return
  if (request.get_method() != m_method)
    return false;

  //! no path matching, return
  params_t params;
  if (!m_matcher.match(request.get_target(), params))
    return false;

  request.set_path(m_path);
  request.set_params(params);

  return true;
}


//!
//! dispatch
//!
void
route::dispatch(const http::request& request, http::response& response) const {
  if (m_callback)
    m_callback(request, response);
}

} // namespace routing

} // namespace netflex
