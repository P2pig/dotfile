# ~/.bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

#PS1='\[\e[1;31m\]\W/ \$ \[\e[0m\]'
#PS1='\[\e[1;31m\](⌐■_■)\[\e[1;31;5m\]b \[\e[0m\]\[\e[1;31m\]\W/$\[\e[0m\] '

# comment
alias r=ranger
alias ls='ls --color=auto'
alias ll='ls -lah --color=auto'
alias grep="grep --color=auto -n"

# git shortcut
alias gl='git log --oneline --all --graph'
alias gll='git log --graph --pretty=format:"%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset" --abbrev-commit --date=relative'
alias gb='git branch'
alias gs='git status -s'

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

