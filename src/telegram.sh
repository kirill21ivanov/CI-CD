#!/bin/bash
if [ "$CI_JOB_STATUS" == "success" ]; then
mess='Все выполнено без ошибок!'
else
mess='Ошибка! Проверьте консоль!'
fi
TELEGRAM_BOT_TOKEN="6505031919:AAEcwQhs7hu9GSIgy-YgIhLHql2cyo3INuo"
TELEGRAM_USER_ID="870163214"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
if [ "$1" == "ci" ]; then
TEXT="Этап CI: $mess%0A%0AProject:+CI/CD School 21%0A"
else
TEXT="Этап CD: $mess%0A%0AProject:+CI/CD School 21%0A"
fi
curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null