#! /bin/bash

# Fixer les variables avec les chemins de vos fichiers
HDA=~/Documents/SAR/NMV/Images/nmv-tp.img 
HDB=~/Documents/SAR/NMV/Images/myHome.img 
#KERNEL=/tmp/linux-4.2.3/arch/x86/boot/bzImage 
KERNEL=~/Cave/linux/arch/x86/boot/bzImage

# Si besoin ajouter une option pour le kernel
#CMDLINE='root=/dev/sda1 rw vga=792 console=ttyS0 kgdboc=ttyS1  init=/bin/bash'
CMDLINE='root=/dev/sda1 rw vga=792 console=ttyS0 kgdboc=ttyS1'

#Exemple d'utilisation du initrd
#exec qemu-system-x86_64 -hda "${HDA}" -hdb "${HDB}" -serial stdio -serial pty -net nic -net user  -boot c -m 1G -kernel "${KERNEL}" -initrd /tmp/m.cpio.gz  -append "${CMDLINE}"
exec qemu-system-x86_64 -hda "${HDA}" -hdb "${HDB}" -serial stdio -serial pty -net nic -net user  -boot c -m 1G -kernel "${KERNEL}"  -append "${CMDLINE}"

