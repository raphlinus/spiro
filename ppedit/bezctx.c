/*
ppedit - A pattern plate editor for Spiro splines.
Copyright (C) 2007 Raph Levien

Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
<LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
option. This file may not be copied, modified, or distributed
except according to those terms.

*/
#include "bezctx.h"

void bezctx_moveto(bezctx *bc, double x, double y, int is_open)
{
    bc->moveto(bc, x, y, is_open);
}

void bezctx_lineto(bezctx *bc, double x, double y)
{
    bc->lineto(bc, x, y);
}

void bezctx_quadto(bezctx *bc, double x1, double y1, double x2, double y2)
{
    bc->quadto(bc, x1, y1, x2, y2);
}

void bezctx_curveto(bezctx *bc, double x1, double y1, double x2, double y2,
                    double x3, double y3)
{
    bc->curveto(bc, x1, y1, x2, y2, x3, y3);
}

void bezctx_mark_knot(bezctx *bc, int knot_idx)
{
    if (bc->mark_knot)
        bc->mark_knot(bc, knot_idx);
}
