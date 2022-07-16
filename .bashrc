# ~/.bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias grep="grep --color=auto -n"
alias ls='ls --color=auto'
alias ll='ls -lah --color=auto'
alias reboot='sudo shutdown -r now'
# wireless switch
alias ws='iwctl station wlan0 scan; sleep 1; iwctl station wlan0 get-networks;'
alias wsoff='iwctl adapter phy0 set-property Powered off'
alias wson='iwctl adapter phy0 set-property Powered on;'
alias gpumon='sudo intel-gpu-overlay --position bottom-right --size 1200x800'
alias gpumonk='sudo pkill intel-gpu-overl'
alias r=ranger
alias gl='git log --oneline --all --graph'
alias gll='git log --graph --pretty=format:"%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset" --abbrev-commit --date=relative'
alias gb='git branch'
alias gs='git status -s'
alias bat="cat /sys/class/power_supply/BAT1/capacity"
PS1='\[\e[1;31m\]\W/ \$ \[\e[0m\]'
#PS1='\[\e[1;31m\](⌐■_■)\[\e[1;31;5m\]b \[\e[0m\]\[\e[1;31m\]\W/$\[\e[0m\] '

alias wsr='sudo systemctl restart iwd'

# screen rotation
alias r0='xrandr -o 0; xinput set-prop "IPTS Touch"  --type=float "Coordinate Transformation Matrix"  1  0 0 0 1 0 0 0 1; xinput set-prop "IPTS Touch"  --type=float "libinput Calibration Matrix"  1  0 0 0 1 0 0 0 1' 
alias r1='xrandr -o 1; xinput set-prop "IPTS Touch"  --type=float "Coordinate Transformation Matrix"  0 -1 1 1 0 0 0 0 1; xinput set-prop "IPTS Touch"  --type=float "libinput Calibration Matrix"  1  0 0 0 1 0 0 0 1'
alias r2='xrandr -o 2'
alias r3='xrandr -o 3'


# brightness
alias br1='echo 1000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'
alias br2='echo 3000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'
alias br3='echo 6000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'
alias br4='echo 9000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'
alias br5='echo 12000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'
alias br6='echo 15000 | sudo tee /sys/class/backlight/intel_backlight/brightness > /dev/null'

export GREP_COLORS='mt=01;31:sl=:cx=:fn=35:ln=32:bn=32:se=36';

