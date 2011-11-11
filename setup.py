#!/usr/bin/env python

import ez_setup
ez_setup.use_setuptools()

from setuptools import setup, Extension

setup(
    name='Murmurhash',
    version='0.1.0',
    license='MIT',
    author='Kyle Teague',
    author_email='kyteague@gmail.com',
    description='MurmurHash1, MurmurHash2, and MurmurHash3 hash functions.',
	ext_modules = [
		Extension('murmurhash', [
            'ext/murmur.cpp',
            'ext/MurmurHash1.cpp',
            'ext/MurmurHash2.cpp',
            'ext/MurmurHash3.cpp',
		],
		depends=[
            'ext/MurmurHash1.h'
            'ext/MurmurHash2.h'
            'ext/MurmurHash3.h'
		],
		language='c++')
	],
    platforms='any',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: C++',
        'Topic :: Software Development',
        'Topic :: Software Development :: Libraries :: Python Modules'
    ],
)

