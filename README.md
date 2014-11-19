# LaZyDev C Library


### System Export Value

* You need to export LZLIB_HOME(the working directory) to .bash_profile or equivaluent.

  example: in .bash_profile

  `export LZLIB_HOME=~/work/lzlib`

---------------------------------------------------------------------------------------


### Components List

* lz_typeconv
  - type conversion component

* lz_datetime
  - datetime component
  - dependency : lz_typeconv

* lz_logger
  - logger component
  - dependency : lz_typeconv, lz_datetime

* lz_hashmap
  - hashmap component
