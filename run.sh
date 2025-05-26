#!/bin/bash

# 프로젝트 루트로 이동 (main.cpp가 있는 폴더 기준)
cd "$(dirname "$0")"

# 빌드 디렉토리 생성
mkdir -p build
cd build

# CMake 설정 및 빌드
cmake .. && make

# 빌드 성공 시 실행
if [ -f "OOP_Tetris" ]; then
  echo "===== 실행 결과 ====="
  ./OOP_Tetris
else
  echo "❌ 실행 파일이 생성되지 않았습니다."
fi