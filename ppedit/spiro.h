typedef struct {
    double x;
    double y;
    char ty;
} spiro_cp;

typedef struct spiro_seg_s spiro_seg;

spiro_seg *
run_spiro(const spiro_cp *src, int n);

void
free_spiro(spiro_seg *s);

void
spiro_to_bpath(const spiro_seg *s, int n, bezctx *bc);

double get_knot_th(const spiro_seg *s, int i);
