#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038
  make -f /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038
  make -f /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038
  make -f /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038
  make -f /Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/CMakeScripts/ReRunCMake.make
fi

