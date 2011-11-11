#include <Python.h>
#include "MurmurHash1.h"
#include "MurmurHash2.h"
#include "MurmurHash3.h"

typedef uint32_t (*hash32_t)(const void * key, int len, uint32_t seed);
typedef uint64_t (*hash64_t)(const void * key, int len, uint64_t seed);

static inline PyObject * murmur_hash_32(PyObject *self, PyObject *args, hash32_t hash)
{
	const char *key;
	int len;
	uint32_t seed = 0;

	if (!PyArg_ParseTuple(args, "t#|I", &key, &len, &seed))
		return NULL;

	return Py_BuildValue("I", hash(key, len, seed));
}

static inline PyObject * murmur_hash_64(PyObject *self, PyObject *args, hash64_t hash)
{
	const char *key;
	int len;
	uint64_t seed = 0;

	if (!PyArg_ParseTuple(args, "t#|I", &key, &len, &seed))
		return NULL;

	return Py_BuildValue("k", hash(key, len, seed));
}

static PyObject * murmur_hash1(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHash1);
}

static PyObject * murmur_hash1_aligned(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHash1Aligned);
}

static PyObject * murmur_hash2(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHash2);
}

static PyObject * murmur_hash2_x64_64(PyObject *self, PyObject *args)
{
    return murmur_hash_64(self, args, MurmurHash64A);
}

static PyObject * murmur_hash2_x86_64(PyObject *self, PyObject *args)
{
    return murmur_hash_64(self, args, MurmurHash64B);
}

static PyObject * murmur_hash2a(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHash2A);
}

static PyObject * murmur_hash2_neutral(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHashNeutral2);
}

static PyObject * murmur_hash2_aligned(PyObject *self, PyObject *args)
{
    return murmur_hash_32(self, args, MurmurHashAligned2);
}

static PyObject * murmur_hash3_x86_32(PyObject *self, PyObject *args)
{
	const char *key;
	int len;
	unsigned int seed = 0;
    uint32_t val;

	if (!PyArg_ParseTuple(args, "t#|I", &key, &len, &seed))
		return NULL;

    MurmurHash3_x86_32(key, len, seed, &val);

	return Py_BuildValue("I", val);
}

static PyObject * murmur_hash3_x86_128(PyObject *self, PyObject *args)
{
	const char *key;
	int len;
	unsigned int seed = 0;
    char val[4 * 4];

	if (!PyArg_ParseTuple(args, "t#|I", &key, &len, &seed))
		return NULL;

    MurmurHash3_x86_128(key, len, seed, &val);

	return Py_BuildValue("s#", val, sizeof(val));
}

static PyObject * murmur_hash3_x64_128(PyObject *self, PyObject *args)
{
	const char *key;
	int len;
	unsigned int seed = 0;
    char val[4 * 4];

	if (!PyArg_ParseTuple(args, "t#|I", &key, &len, &seed))
		return NULL;

    MurmurHash3_x86_128(key, len, seed, &val);

	return Py_BuildValue("s#", val, sizeof(val));
}

static PyMethodDef ext_methods[] = {
    {"hash1", murmur_hash1, METH_VARARGS, "Returns a 32-bit MurmurHash1"},
    {"hash1_aligned", murmur_hash1_aligned, METH_VARARGS, "Returns a 32-bit MurmurHash2 using aligned reads"},
    {"hash2", murmur_hash2, METH_VARARGS, "Returns a 32-bit MurmurHash2"},
    {"hash2_x64_64", murmur_hash2_x64_64, METH_VARARGS, "Returns a 64-bit MurmurHash2 optimized for x64 systems"},
    {"hash2_x86_64", murmur_hash2_x86_64, METH_VARARGS, "Returns a 64-bit MurmurHash2 optimized for x86 systems"},
    {"hash2a", murmur_hash2a, METH_VARARGS, "Returns a 32-bit MurmurHash2 using Merkle-Damgard construction"},
    {"hash2_neutral", murmur_hash2_neutral, METH_VARARGS, "Returns a 32-bit MurmurHash2 that is endian and alignment neutral"},
    {"hash2_aligned", murmur_hash2_aligned, METH_VARARGS, "Returns a 32-bit MurmurHash2 using aligned reads"},
    {"hash3", murmur_hash3_x86_32, METH_VARARGS, "Returns a 32-bit MurmurHash3"},
    {"hash3_x86_128", murmur_hash3_x86_128, METH_VARARGS, "Returns a 128-bit MurmurHash3 optimized for x86 systems"},
    {"hash3_x64_128", murmur_hash3_x64_128, METH_VARARGS, "Returns a 128-bit MurmurHash3 optimized for x64 systems"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initmurmur()
{
    Py_InitModule("murmurhash", ext_methods);
}

