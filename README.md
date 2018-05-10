


TP FINAL C++ - TALLER DE PROGRAMACION I
==========

[![Build Status](https://travis-ci.com/gabyrobles93/tp-final-taller.svg?token=Qx8C9xtSVWpLJwsqc4hb&branch=master)](https://travis-ci.com/gabyrobles93/tp-final-taller)

Código y notas del proyecto final de Taller de Programación I - FIUBA


| Padrón | Nombre y Apellido         |
|--------|---------------------------|
| 97893 | ALVAREZ WINDEY ARIEL JUSTO |
| 98546 | DIZ GONZALO                |
| 95897 | GABRIEL ROBLES             |

Tablero de tareas en TRELLO:
https://trello.com/b/opoeIXXF/worms-tp-final

# Tutorial de uso de CxxTest:

1) Descargar cxxtest generator
```bash
 $ sudo apt-get install cxxtest
```

2) Escribir casos de pruebas en un .h, como en el siguiente ejemplo:

```c++
#ifndef __MY_TEST_CASES_H__
#define __MY_TEST_CASES_H__

 #include <cxxtest/TestSuite.h>

  class MyTestSuite : public CxxTest::TestSuite {
      public:
          void testAddition(void) {
              TS_ASSERT(1+1>1);
              TS_ASSERT_EQUALS(1+1,2);
          }
  };

  #endif
```
3) Generar casos de prueba:
```bash
 $ cxxtestgen --error-printer -o runner.cpp MyTestSuite1.h
```

4) Compilar casos de prueba:
```bash
  $ g++ -o runner runner.cpp
```

5) Ejecutar casos de prueba:
```bash
 $ ./runner
```

Para más información ver [guía oficial de uso de cxxtest](test_cases/guide.pdf)
