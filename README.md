# Лог команд
## Создание и переход в рабочую директорию
cd ./Downloads/Programming
mkdir Laba6
cd ./Laba6
## Клонирование репозитория Куртяника Д.В.
git clone https://github.com/Kurtyanik/LR6/
## Конфигурация пользователя
git config --global user.name "4117 Kononov Svyatoslav Igorevich"
git config --global user.email "harik10346@gmail.com"
## Клонирование личного репозитория и переход в его локальную директорию
git clone https://github.com/slava233/CGSG/
cd ./CGSG
## Создание побочной ветки и взятие её под контроль
git branch update-readme
git checkout update-readme
## Копирование файла README.md и его запрос на добавление в репозиторий
cp ../LR6/README.md ./
git add README.md
## Создание коммита и его публикация в сеть
git commit -m "add README.md file"
git push -u origin update-readme
## Взятие под контроль основной ветки и её слияние с побочной
git checkout main
git merge update-readme
## Удаление побочной ветки
git branch -d update-readme
git push -u origin main
## Получение истории коммитов
git log
## Возвращение к предыдущему коммиту
git reset --hard e450835676981444965b2223ecfebaeef0d459b0
git push -f origin main
## Создание побочной ветки отчёта
git branch university-report
## Создание директории для скриншотов
mkdir Screenshots
## Копирование отчёта и скриншотов в локальную директорию репозитория
cp ../../../../*.png ./Screenshots
cp ../LR6/README.md ./
## Взятие под контроль побочной ветки отчёта
git checkout university-report
## Запрос на добавление в репозиторий скопированных файлов
git add README.md
git add ./Screenshots/*.png
## Создание коммита и его публикация в сеть
git commit -m "add README.md and screenshots"
git push -u origin university-report
# Скриншоты
![История команд №1](/Screenshots/Screenshot_20221103_225245.png)
![История команд №2](/Screenshots/Screenshot_20221103_225330.png)
![История коммитов](/Screenshots/Screenshot_20221103_224053.png)