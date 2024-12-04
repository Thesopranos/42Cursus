#### RENKLER ####
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
ENDCOLOR="\e[0m"
RESET="\e[0m"

### --- 42 --- ###

# Aliases -- 42 -- #
alias .c="clear"
alias mf="make fclean"
alias mc="make clean"
alias mr="make re"
alias ma="make all"
alias valg="leaks -atExit -q --"
alias gccw='gcc -Wall -Wextra -Werror -o test'
alias gacct='find . -type f -name "*.c" -exec gcc -Wall -Wextra -Werror {} -o test \; && tt'

# ls42: 42Cursus dizinlerini numaralandırarak listeler
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

# go42: Sayıya veya dizin adına göre 42Cursus alt dizinine gider
function go42() {
    echo " "
    local target=""
    local i=1

    if [[ -z "$1" ]]; then
        echo -e "${RED}Kullanım: go42 <dizin numarası veya adı>${ENDCOLOR}\n"
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

# get42: Sayıya veya dizin adına göre dizini masaüstüne kopyalar
function get42() {
    echo " "
    local target=""
    local i=1

    # Kullanıcıdan parametre alınmazsa, hata mesajı ver
    if [[ -z "$1" ]]; then
        echo -e "${RED}Kullanım: get42 <dizin numarası veya adı>${ENDCOLOR}\n"
        return 1
    fi

    # Parametre sayısal bir değer ise, numaraya göre dizin bul
    if [[ "$1" =~ ^[0-9]+$ ]]; then
        for dir in ~/42Cursus/*/; do
            if [[ $i -eq $1 ]]; then
                target="$dir"
                break
            fi
            ((i++))
        done
    else
        # Parametre bir dizin adı ise, adıyla eşleşen dizini bul
        for dir in ~/42Cursus/*/; do
            if [[ "$(basename "$dir")" == "$1" ]]; then
                target="$dir"
                break
            fi
        done
    fi

    # Eğer hedef dizin bulunamadıysa, hata mesajı ver
    if [[ -z "$target" ]]; then
        echo -e "${RED}Hata: Dizin bulunamadı.${ENDCOLOR}\n"
        return 1
    fi

    # Masaüstüne kopyalamayı gerçekleştir
    local desktop_dir=~/Desktop
    local dest="$desktop_dir/$(basename "$target")"

    if cp -r "$target" "$dest"; then
        echo -e "${GREEN}Başarıyla kopyalandı: ${BLUE}$(basename "$target")${ENDCOLOR} -> ${BLUE}$dest${ENDCOLOR}"
    else
        echo -e "${RED}Hata: Dizin kopyalanamadı.${ENDCOLOR}\n"
        return 1
    fi
    echo " "
}

# pull42: 42Cursus deposunu günceller
function pull42() {
    echo " "
    cd ~/42Cursus && git pull \
        && echo -e "${GREEN}Depo başarıyla güncellendi.${ENDCOLOR}" \
        || echo -e "${RED}Hata: Güncelleme başarısız.${ENDCOLOR}"
    echo " "
}

# update42c: 42Cursus deposuna değişiklik gönderir
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
