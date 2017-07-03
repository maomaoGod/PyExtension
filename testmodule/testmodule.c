
#include <Python.h>      //����pythonͷ�ļ�  

#pragma comment(lib,"python35")

//�� first step: define the c function
static int fac(int n) {
	if (n < 2)
		return 1;
	return n * fac(n - 1);
}

static char *reverse(char *s) {
	register char t;
	char *p = s;
	char *q = (s + (strlen(s) - 1));
	while (p < q) {
		t = *p;
		*p++ = *q;
		*q-- = t;
	}
	return s;
}

//�� second step:use cpython to wrap the defined func
//   the func type must be static and return value must be PyObject*

//fac�����İ�װ����    
static PyObject *
wrap_fac(PyObject *self, PyObject *args) {
	int num;
	if (!(PyArg_ParseTuple(args, "i", &num))) {
		return NULL;
	}
	return (PyObject *)Py_BuildValue("i", fac(num));
}


//reverse�����İ�װ����  
static PyObject *
wrap_doppel(PyObject *self, PyObject *args) {
	char *orignal;
	char *reversed;
	PyObject * retval;
	if (!(PyArg_ParseTuple(args, "s", &orignal))) {
		return NULL;
	}
	retval = (PyObject *)Py_BuildValue("ss", orignal, reversed = reverse(_strdup(orignal)));
	free(reversed);
	return retval;
}

//�� third step: list its name and address in a ��method table��
//Ϊģ�鴴��һ��������Ϣ������  
static PyMethodDef
ExtestMethods[] = {
	{ "fac", wrap_fac, METH_VARARGS,"a fac method" },
	{ "doppel", wrap_doppel, METH_VARARGS ,"a string reverse method"},
	{NULL,NULL,0,NULL}
};


// �� forth step:  method table must be referenced in the module definition structure
static struct PyModuleDef ExtestModule = {
	PyModuleDef_HEAD_INIT,
	"testmodule",   /* name of module */
	NULL,           /* module documentation, may be NULL */
	-1,             /* size of per-interpreter state of the module,or -1 if the module keeps state in global variables. */
    ExtestMethods
};

//�� fifth step: pass the module structure to the module init function
//The initialization function must be named PyInit_name(), where name is the name of the module, 
//and should be the only non-static item defined in the module file:
 
PyMODINIT_FUNC
PyInit_testmodule(void)
{
	PyObject *m;

	m = PyModule_Create(&ExtestModule);
	if (m == NULL)
		return NULL;

	/*SpamError = PyErr_NewException("spam.error", NULL, NULL);
	Py_INCREF(SpamError);
	PyModule_AddObject(m, "error", SpamError);*/
	return m;
}
