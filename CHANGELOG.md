# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## Unreleased

### Added

- Basic API authentication to protect exposure of API port to the internet [#1228](https://github.com/ethereum-mining/ethminer/pull/1228).
- Add `ispaused` information into response of `miner_getstathr` API query [#1232](https://github.com/ethereum-mining/ethminer/pull/1232).
- API responses return "ethminer-" as version prefix. [#1300](https://github.com/ethereum-mining/ethminer/pull/1300).
- Stratum mode autodetection. No need to specify stratum+tcp or stratum1+tcp or stratum2+tcp
- Connection failed due to login errors (wrong address or worker) are marked Unrecoverable and no longer used
- Replaced opencl kernel with opensource jawawawa opencl kernel
- Added support for jawawawa AMD binary kernels
- AMD auto kernel selection. Try bin first, if not fall back to opencl.
- API: New method `miner_setverbosity`. [#1382](https://github.com/ethereum-mining/ethminer/pull/1382).

## 0.15.0rc1

### Fixed

- Restore the ability to auto-config OpenCL work size [#1225](https://github.com/ethereum-mining/ethminer/pull/1225).
- The API server totally broken fixed [#1227](https://github.com/ethereum-mining/ethminer/pull/1227).


## 0.15.0rc0

### Added

- Add `--tstop` and `--tstart` option preventing GPU overheating [#1146](https://github.com/ethereum-mining/ethminer/pull/1146), [#1159](https://github.com/ethereum-mining/ethminer/pull/1159).
- Added information about ordering CUDA devices in the README.md FAQ [#1162](https://github.com/ethereum-mining/ethminer/pull/1162).

### Fixed

- Reconnecting with mining pool improved [#1135](https://github.com/ethereum-mining/ethminer/pull/1135).
- Stratum nicehash. Avoid recalculating target with every job [#1156](https://github.com/ethereum-mining/ethminer/pull/1156).
- Drop duplicate stratum jobs (pool bug workaround) [#1161](https://github.com/ethereum-mining/ethminer/pull/1161).
- CLI11 command line parsing support added [#1160](https://github.com/ethereum-mining/ethminer/pull/1160).
- Farm mode (get_work): fixed loss of valid shares and increment in stales [#1215](https://github.com/ethereum-mining/ethminer/pull/1215).
- Stratum implementation improvements [#1222](https://github.com/ethereum-mining/ethminer/pull/1222).
- Build fixes & improvements [#1214](https://github.com/ethereum-mining/ethminer/pull/1214).

### Removed

- Disabled Debug configuration for Visual Studio [#69](https://github.com/ethereum-mining/ethminer/issues/69) [#1131](https://github.com/ethereum-mining/ethminer/pull/1131).
