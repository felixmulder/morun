#include <string.h>

#include "run.h"

void run_prog(const gchar *prog)
{
        if (strcmp(prog, "") == 0)
                return;

        popen(prog, "r");
}
