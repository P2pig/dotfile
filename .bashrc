#
# ~/.bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
# PS1='[\u@\h \W]\$ '
#PS1='\[\e[1;31m\](⌐■_■)ノ \W/$\[\e[00m\] '
PS1='\[\e[1;31m\](⌐■_■)\[\e[1;31;5m\]b \[\e[0m\]\[\e[1;31m\]\W/$\[\e[0m\] '

alias v='nvim'
alias vim='nvim'
alias chrome='chromium &'
alias ls='ls --color=auto'
alias l='ls -lt --color=auto'
alias ll='ls -la --color=auto'
alias sshpi='ssh pi@172.20.10.4'
alias shairport='sudo systemctl restart shairport-sync'
alias sch='xrandr -s 0 && source .fehbg'
alias sch1='xrandr -s 19 && source .fehbg'
alias scr-full='flameshot full -p .'

# ---------My Setting---------
# sudo ifconfig ens3 172.20.10.3

export PAGER="most"

# set keyboard input rate
if pgrep -x "startx" > /dev/null 
then
	# set key input rate
	xset r rate 300 50
	
	#set background image
	source .fehbg

fi

# arm compiler
 export PATH="$PATH:/usr/local/git/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin"

# nvm
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
