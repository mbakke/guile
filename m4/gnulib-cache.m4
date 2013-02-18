# Copyright (C) 2002-2013 Free Software Foundation, Inc.
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file.  If not, see <http://www.gnu.org/licenses/>.
#
# As a special exception to the GNU General Public License,
# this file may be distributed as part of a program that
# contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the specification of how gnulib-tool is used.
# It acts as a cache: It is written and read by gnulib-tool.
# In projects that use version control, this file is meant to be put under
# version control, like the configure.ac and various Makefile.am files.


# Specification in the form of a command-line invocation:
#   gnulib-tool --import --dir=. --local-dir=gnulib-local --lib=libgnu --source-base=lib --m4-base=m4 --doc-base=doc --tests-base=tests --aux-dir=build-aux --lgpl=3 --no-conditional-dependencies --libtool --macro-prefix=gl --no-vc-files accept alignof alloca-opt announce-gen autobuild bind byteswap canonicalize-lgpl ceil clock-time close connect dirfd duplocale environ extensions flock floor fpieee frexp full-read full-write func gendocs getaddrinfo getpeername getsockname getsockopt git-version-gen gitlog-to-changelog gnu-web-doc-update gnupload havelib iconv_open-utf inet_ntop inet_pton isinf isnan ldexp lib-symbol-versions lib-symbol-visibility libunistring listen localcharset locale log1p maintainer-makefile malloc-gnu malloca nl_langinfo nproc open pipe2 putenv recv recvfrom regex rename send sendto setenv setsockopt shutdown socket stat-time stdlib strftime striconveh string sys_stat trunc verify vsnprintf warnings wchar

# Specification in the form of a few gnulib-tool.m4 macro invocations:
gl_LOCAL_DIR([gnulib-local])
gl_MODULES([
  accept
  alignof
  alloca-opt
  announce-gen
  autobuild
  bind
  byteswap
  canonicalize-lgpl
  ceil
  clock-time
  close
  connect
  dirfd
  duplocale
  environ
  extensions
  flock
  floor
  fpieee
  frexp
  full-read
  full-write
  func
  gendocs
  getaddrinfo
  getpeername
  getsockname
  getsockopt
  git-version-gen
  gitlog-to-changelog
  gnu-web-doc-update
  gnupload
  havelib
  iconv_open-utf
  inet_ntop
  inet_pton
  isinf
  isnan
  ldexp
  lib-symbol-versions
  lib-symbol-visibility
  libunistring
  listen
  localcharset
  locale
  log1p
  maintainer-makefile
  malloc-gnu
  malloca
  nl_langinfo
  nproc
  open
  pipe2
  putenv
  recv
  recvfrom
  regex
  rename
  send
  sendto
  setenv
  setsockopt
  shutdown
  socket
  stat-time
  stdlib
  strftime
  striconveh
  string
  sys_stat
  trunc
  verify
  vsnprintf
  warnings
  wchar
])
gl_AVOID([])
gl_SOURCE_BASE([lib])
gl_M4_BASE([m4])
gl_PO_BASE([])
gl_DOC_BASE([doc])
gl_TESTS_BASE([tests])
gl_LIB([libgnu])
gl_LGPL([3])
gl_MAKEFILE_NAME([])
gl_LIBTOOL
gl_MACRO_PREFIX([gl])
gl_PO_DOMAIN([])
gl_WITNESS_C_MACRO([])
gl_VC_FILES([false])
