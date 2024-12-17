export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="bira"

setxkbmap -option ctrl:swap_lwin_lctl

plugins=(git)

source $ZSH/oh-my-zsh.sh

#### RENKLER ####
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
ENDCOLOR="\e[0m"
RESET="\e[0m"
alias zshrc="vim ~/.zshrc"

### --------------------- 42 ---------------------- ###

# Aliases --------------- 42 --------------- #
alias .c="clear"
alias cls="clear"
alias godesktop="cd ~/Masaüstü"
alias mf="make fclean"
alias mc="make clean"
alias mr="make re"
alias ma="make all"
alias valg="leaks -atExit -q --"
alias gccw='gcc -Wall -Wextra -Werror -o test'
alias gacct='find . -type f -name "*.c" -exec gcc -Wall -Wextra -Werror {} -o test \; && tt'

# Functions ------------- 42 --------------- #
function ls42() {
    echo " "
    local i=1
    local columns=2
    local format="${YELLOW}%2d:${ENDCOLOR} ${BLUE}%-20s${ENDCOLOR}"
    local line=""

    for dir in ~/42Cursus/*/; do
        local base_name=$(basename "$dir")

        line+=$(printf "$format" $i "$base_name")
        ((i++))

        if (( (i - 1) % columns == 0 )); then
            echo -e "$line"
            line=""
        fi
    done

    if [[ -n "$line" ]]; then
        echo -e "$line"
    fi

    if (( i == 1 )); then
        echo -e "${RED}Hiçbir dizin bulunamadı.${ENDCOLOR}"
    fi
    echo " "
    return 0
}

function go42() {
    echo " "
    local target=""
    local i=1

    if [[ -z "$1" ]]; then
        cd ~/42Cursus
        echo -e "${GREEN}Başarıyla geçiş yapıldı: ${BLUE}42Cursus${ENDCOLOR}\n"
        return 1
    fi

    if [[ "$1" =~ ^[0-9]+$ ]]; then
        for dir in ~/42Cursus/*/; do
            if [[ $i -eq $1 ]]; then
                target="$dir"
                break
            fi
            ((i++))
        done
    else
        for dir in ~/42Cursus/*/; do
            if [[ "$(basename "$dir")" == "$1" ]]; then
                target="$dir"
                break
            fi
        done
    fi

    if [[ -z "$target" ]]; then
        echo -e "${RED}Hata: Dizin bulunamadı.${ENDCOLOR}\n"
        return 1
    fi

    cd "$target" && echo -e "${GREEN}Başarıyla geçiş yapıldı: ${BLUE}$(basename "$target")${ENDCOLOR}"
    echo " "
}

function get42() {
    pull42
    local target=""
    local i=1

    if [[ -z "$1" ]]; then
	ls42
        echo -e "${RED}Kullanım: get42 <dizin numarası veya adı>${ENDCOLOR}\n"
        return 1
    fi

    if [[ "$1" =~ ^[0-9]+$ ]]; then
        for dir in ~/42Cursus/*/; do
            if [[ $i -eq $1 ]]; then
                target="$dir"
                break
            fi
            ((i++))
        done
    else
        for dir in ~/42Cursus/*/; do
            if [[ "$(basename "$dir")" == "$1" ]]; then
                target="$dir"
                break
            fi
        done
    fi

    if [[ -z "$target" ]]; then
        echo -e "${RED}Hata: Dizin bulunamadı.${ENDCOLOR}\n"
        return 1
    fi
    local desktop_dir=~/Desktop
    local dest="$desktop_dir/$(basename "$target")"

    if [[ -d "$dest" ]]; then
        echo -e "${YELLOW}Uyarı: ${BLUE}$(basename "$target")${ENDCOLOR} zaten masaüstünde mevcut.${ENDCOLOR}"
    else
        if cp -r "$target" "$dest"; then
            echo -e "${GREEN}Başarıyla kopyalandı: ${BLUE}$(basename "$target")${ENDCOLOR} -> ${BLUE}$dest${ENDCOLOR}"
        else
            echo -e "${RED}Hata: Dizin kopyalanamadı.${ENDCOLOR}\n"
            return 1
        fi
    fi
    echo " "
}

function pull42() {
    echo " "
    cd ~/42Cursus && git pull \
        && echo -e "${GREEN}Depo başarıyla güncellendi.${ENDCOLOR}" \
        || echo -e "${RED}Hata: Güncelleme başarısız.${ENDCOLOR}"
    echo " "
}

function update42c() {
    echo " "
    if [[ -z "$1" ]]; then
        echo -e "${RED}Kullanım: update42c <commit mesajı>${ENDCOLOR}\n"
        return 1
    fi

    cd ~/42Cursus && git add . && git commit -m "$1" && git push \
        && echo -e "${GREEN}Değişiklikler başarıyla gönderildi: ${BLUE}$1${ENDCOLOR}" \
        || echo -e "${RED}Hata: Gönderim başarısız.${ENDCOLOR}"
    echo " "
}

42profile() {
    local username=$1

    if [ -z "$username" ]; then
        echo -e "\e[31mHata: Kullanıcı adı belirtilmedi.\e[0m"
        return 1
    fi

    local url="https://profile.intra.42.fr/users/${username}"

    xdg-open "$url" 2>/dev/null
}

githprofile() {
    local username=$1

    if [ -z "$username" ]; then
        echo -e "\e[31mHata: GitHub kullanıcı adı belirtilmedi.\e[0m"
        return 1
    fi

    local url="https://github.com/${username}"

    xdg-open "$url" 2>/dev/null
}
