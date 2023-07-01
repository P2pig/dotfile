#!/bin/sh
exec picom &
exec dwmstatus 2>&1 >/dev/null &
exec fcitx5 &
# exec mpv --loop=inf ~/Music/Lineage-giran.mp3 &

# systemctl --user import-environment DISPLAY XAUTHORITY

#sh -c "feh --no-fehbg --bg-scale -z /home/ducky/Pictures/arch_wallpaper.jpg"
feh --bg-max ~/Pictures/water-paintingmoon-archangelwarframe-bar-lighting-intricated-complex-head-and-shoulder-774958196.png

export QT_AUTO_SCREEN_SCALE_FACTOR=2
export QT_SCALE_FACTOR=2
export GDK_SCALE=1
export GDK_DPI_SCALE=2

exec dwm
