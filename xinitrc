#!/bin/sh

# disable cpu turbo (cnt be use)
# echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo

# set max cpu frequence
# cpupower frequency-set -u clock_freq GHz

# color temperture
#redshift -P -O 5400; 
#redshift -P -O 3600;

# key rate
xset r rate 170 20; 

# compositor
# picom &

# feh
#feh --no-fehbg --bg-scale -z /home/ducky/Downloads/Wallpaper/*.jpg &
# exec newbg

# libinput-gestures
#/usr/bin/libinput-gestures &

# dbus
#dbus-launch &
# env dbus-launch --auto-syntax fcitx-autostart &
# eval --auto-syntax 

# fcitx
fcitx-autostart &

# status bar
~/.config/script/statusBar.sh &

# flameshot
#flameshot &

# linux-clicky
# ( cd ~/.config/typer/linux-clicky/ && ./main.py &)

# ranger
export RANGER_LOAD_DEFAULT_RC=FALSE

# GTK3
export GDK_SCALE=2
export GDK_DPI_SCALE=1

# QT5
export QT_AUTO_SCREEN_SCALE_FACTOR=2
export QT_SCREEN_SCALE_FACTORS=2

exec dwm
