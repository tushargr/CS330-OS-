make all
cp gemOS.kernel ../../assignment1/gemOS/gem5/gemos/binaries/
pushd ../../assignment1/gemOS/gem5
export M5_PATH=/home/tushar/Desktop/5thsem/OS/assignment1/gemOS/gem5/gemos
build/X86/gem5.opt configs/example/fs.py
popd
