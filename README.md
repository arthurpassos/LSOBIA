# LSOBIA

OTB Module providing Large Scale Object Based Image Analysis functionalities.

Dependencies
===========
* [OTB](https://www.orfeo-toolbox.org/)
* MPI (developped and validated with mpich-3.2)


How to build it
==============
LSOBIA can be built like any other [otb remote module](https://wiki.orfeo-toolbox.org/index.php/How_to_write_a_remote_module)
You can build it either from within OTB's sources or outside it.


How to use it
============
LSOBIA provides an OTBApplication, LSSegmentation (Large Scale Segmentation).

Monoprocessor execution :

```bash
  otbcli_LSSegmentation "-io.im" "${INPUT_IMAGE}" "-io.out" "${OUTPUT_DIRECTORY}" "-io.temp" "${TEMP}" "-algorithm" "baatz" "-algorithm.baatz.numitfirstpartial" "5" "-algorithm.baatz.numitpartial" "5" "-algorithm.baatz.stopping" "40" "-algorithm.baatz.spectralweight" "0.5" "-algorithm.baatz.geomweight" "0.5" "-algorithm.baatz.aggregategraphs" "on" "-processing.writeimages" "on" "-processing.writegraphs" "on" "-processing.memory" "2000" "-processing.maxtilesizex" "1000" "-processing.maxtilesizey" "1000"
```

Multiprocessor execution :

Simply add *mpirun -np ${NUM_PROC}* 

```bash
  mpirun -np 4 otbcli_LSSegmentation "-io.im" "${INPUT_IMAGE}" "-io.out" "${OUTPUT_DIRECTORY}" "-io.temp" "${TEMP}" "-algorithm" "baatz" "-algorithm.baatz.numitfirstpartial" "5" "-algorithm.baatz.numitpartial" "5" "-algorithm.baatz.stopping" "40" "-algorithm.baatz.spectralweight" "0.5" "-algorithm.baatz.geomweight" "0.5" "-algorithm.baatz.aggregategraphs" "on" "-processing.writeimages" "on" "-processing.writegraphs" "on" "-processing.memory" "2000" "-processing.maxtilesizex" "1000" "-processing.maxtilesizey" "1000"
```

This produces an image output containing labels of the Baatz Segmentation algorithm.

You can find useful application and binaries execution examples in the unitary tests. To enable these tests, simply build the module with BUILD_TESTING=ON.


Output Samples
==============


Todo
====


Licence
=======
Please see the license for legal issues on the use of the software.
