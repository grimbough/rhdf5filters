/* do not remove */

#include <Rdefines.h>
#include <R_ext/Rdynload.h>

R_CallMethodDef callMethods[] = {
    {NULL, NULL, 0}
};

void R_init_Rhdf5lib(DllInfo *info)
{
    R_registerRoutines(info, NULL, callMethods, NULL, NULL);
    R_useDynamicSymbols(info, TRUE);
}