# makefileを作成
cmake -B build -G Ninja --toolchain ./toolchain-minGW.cmake -DCMAKE_MAKE_PROGRAM=ninja

# ビルド
cmake --build build
