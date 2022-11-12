
if test "`whoami`" != "root" ; then
	echo "You must be logged in as root to build (for loopback mounting)"
	echo "Enter 'su' or 'sudo bash' to switch to root"
	exit
fi


if [ ! -e disk_imgs/vidhios.flp ]
then
	echo ">>> Creating new vidhios floppy image..."
	mkdosfs -C disk_imgs/vidhios.flp 1440 || exit
fi


echo ">>> Assembling bootloader..."

nasm -O0 -w+orphan-labels -f bin -o source/boot/boot.bin source/boot/boot.asm || exit


echo ">>> Assembling vidhios OS kernel..."

cd source
nasm -O0 -w+orphan-labels -f bin -o kernel.bin kernel.asm || exit
cd ..



echo ">>> Adding bootloader to floppy image..."

dd status=noxfer conv=notrunc if=source/boot/boot.bin of=disk_imgs/vidhios.flp || exit


echo ">>> Copying vidhios kernel and programs..."

rm -rf tmp-loop

mkdir tmp-loop && mount -o loop -t vfat disk_imgs/vidhios.flp tmp-loop && cp source/kernel.bin tmp-loop/

cp programs/sample.pcx tmp-loop

sleep 0.2

echo ">>> Unmounting loopback floppy..."

umount tmp-loop || exit

rm -rf tmp-loop


echo ">>> Creating CD-ROM ISO image..."

rm -f disk_imgs/vidhios.iso
mkisofs -quiet -V 'vidhios OS' -input-charset iso8859-1 -o disk_imgs/vidhios.iso -b vidhios.flp disk_imgs/ || exit

echo '>>> Done!'

