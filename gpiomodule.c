//本家ドキュメント ->  https://docs.python.jp/3/extending/extending.html
//コンパイル -> https://docs.python.jp/3/extending/building.html#building
//WebPage -> https://qiita.com/montblanc18/items/6fde59ff6dd30651ad4f
//WebPage -> https://qiita.com/nabion/items/594fb3316583130a636e

#include <Python.h>
#include <wiringPi.h>
/* 
   "Python.h"は<stdio.h>, <string.h>, <error.h>, <stdlib.h>をインクルードしている。
   もしもstdlib.hファイルがなければ、Python.hがmalloc(), free(), realloc()を直接定義する。
 */

// self引数は、モジュールレベルの関数であればモジュールが、メソッドにはオブジェクトインスタンスが渡される。
// agrs引数は、引数の入ったPythonタプルオブジェクトへのポインタになる。
static PyObject *
gpio_system(PyObject *self, PyObject *args){
  const char *command;
  int sts;

  /*
	PyArg_ParseTuple()は引数の型をチェックし、Cの値に変換する。
	すべての引数が正しい方を持っていないと、Falseを返す。 --> 呼び出し側でNULLを返すようにする。
	Pythonインタプリタ全体の取り決めとして、
	関数が処理に失敗した場合はエラーを示す値（通常はNULLポインタ）を返さなければならない
  */
  if(!PyArg_ParseTuple(args, "s", &command)){
	return NULL;
  }  
  sts = system(command);

  /*
	PyLong_FromLong(long v):
	引数vから新たなPyLongObjectを生成して返す。失敗した時はNULLを返す。
	この例だと、Py_BuildValue()として整数オブジェクトを返す。
	もしもvoidを返す関数が期待されている場合、
	return Py_None;
	のようにする。
   */
  return PyLong_FromLong(sts);
}

static PyObject *
gpio_wiringPiSetup(PyObject *self, PyObject *args){
  int ret = wiringPiSetup();
  return Py_BuildValue("i", ret);
}

static PyObject *
gpio_wiringPiSetupPhys(PyObject *self, PyObject *args){
  int ret = wiringPiSetupPhys();
  return Py_BuildValue("i", ret);
}

static PyObject *
gpio_physPinToGpio(PyObject *self, PyObject *args){
  int pin;
  if (!PyArg_ParseTuple(args, "i", &pin)) {
	return NULL;
  }
  int gpio = physPinToGpio(pin);
  return Py_BuildValue("i", gpio);
}

static PyObject *
gpio_getAlt(PyObject *self, PyObject *args){
  int pin;
  if (!PyArg_ParseTuple(args, "i", &pin)) {
	return NULL;
  }
  int alt = getAlt(pin);
  return Py_BuildValue("i", alt);
}

static PyObject *
gpio_pinMode(PyObject *self, PyObject *args){
  int pin;
  int mode;
  if (!PyArg_ParseTuple(args, "ii", &pin, &mode)) {
	return NULL;
  }
  pinMode(pin, mode);
  return Py_BuildValue("");
}

static PyObject *
gpio_pullUpDnControl(PyObject *self, PyObject *args){
  int pin;
  int pud;
  if (!PyArg_ParseTuple(args, "ii", &pin, &pud)) {
	return NULL;
  }
  pullUpDnControl(pin, pud);
  return Py_BuildValue("");
}

static PyObject *
gpio_digitalWrite(PyObject *self, PyObject *args){
  int pin;
  int value;
  if (!PyArg_ParseTuple(args, "ii", &pin, &value)) {
	return NULL;
  }
  digitalWrite(pin, value);
  return Py_BuildValue("");
}

static PyObject *
gpio_digitalRead(PyObject *self, PyObject *args){
  int pin;
  if (!PyArg_ParseTuple(args, "i", &pin)) {
	return NULL;
  }
  int value = digitalRead(pin);
  return Py_BuildValue("i", value);
}


// モジュールのメソッドテーブルと初期化関数を用意する
/*
  gpio_system()をPythonプログラムから呼ぶために、関数名とアドレスをmethod tableに列挙する。
 */

static PyMethodDef GpioMethods[] = {
  {"system", gpio_system, METH_VARARGS, "Execute a shell command."},
  {"wiringPiSetup", gpio_wiringPiSetup, METH_VARARGS, "wiringPiSetup."},
  {"wiringPiSetupPhys", gpio_wiringPiSetupPhys, METH_VARARGS, "wiringPiSetupPhys."},
  {"physPinToGpio", gpio_physPinToGpio, METH_VARARGS, "physPinToGpio."},
  {"getAlt", gpio_getAlt, METH_VARARGS, "getAlt."},
  {"pinMode", gpio_pinMode, METH_VARARGS, "pinMode."},
  {"pullUpDnControl", gpio_pullUpDnControl, METH_VARARGS, "pullUpDnControl."},
  {"digitalWrite", gpio_digitalWrite, METH_VARARGS, "digitalWrite."},
  {"digitalRead", gpio_digitalRead, METH_VARARGS, "digitalRead."},
  {NULL, NULL, 0, NULL} /* Sentinel */
};

/*
{
  method tableはモジュール定義の構造体から参照されている必要
*/
static struct PyModuleDef gpiomodule = {
  PyModuleDef_HEAD_INIT,
  "gpio", /* name of module */
  NULL, /* module documentation, may be NULL */
  -1, /* size of per-interprenter state of the module,
	   or -1 if the module keep state in global variables */
  GpioMethods
};

/*
  この構造体を、モジュール初期化関数内でインタプリタに渡さねばならない。
  モジュール名を"name"としたとき、初期化関数について
  ・名前はPyInit_name()でなければならない。
  ・モジュールファイル内で定義されているものの内、唯一の非static要素でなければならない。
*/
PyMODINIT_FUNC
PyInit_gpio(void){
  return PyModule_Create(&gpiomodule);
}

/* 
   PyMODINIT_FUNCは戻り値をPyObject+になるよう宣言
   gpioモジュールが初めてimportされると、このPyInit_gpio()が呼ばれる。
   すると、
   PyInit_gpioが呼ばれる
   -> PyModule_Createが呼ばれる
   -> PyMethodDefにもとづいて作られたモジュールに組み込み関数オブジェクトが挿入され、そのポインタが返る。
*/


/*
  Pythonへ埋め込むときには、PyImport_AppendInittab()を使って、初期化テーブルにモジュールを追加する。
  その後に、オプションでモジュールをimportする。
*/
int main(int argc, char *argv[]){
  // wchar_t: ワイド文字(=通常よりも1文字あたりのバイト数が多い)から構成されるワイド文字列
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if(program==NULL){
	fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
	exit(1);
  }

  /* Add a built-in module, before Py_Initialize */
  PyImport_AppendInittab("gpio", PyInit_gpio);

  /* Pass argv[0] to the Python interpreter */
  Py_SetProgramName(program);

  /* Initialize the Python interpreter. Required. */
  Py_Initialize();

  /* Optionally import the module; alternatively,
	 import can be deferred until the embedded script
	 imports it.*/
  PyImport_ImportModule("gpio");

  PyMem_RawFree(program);
  return 0;
  
}
