from aiogram.types import BotCommand

#Файл команд бота
private = [
    BotCommand(command='menu', description='Посмотреть меню'),
    BotCommand(command='about', description='О нас'),
    BotCommand(command='payment', description='Варианты оплаты'),
    BotCommand(command='shipping', description='Варианты доставки'),
    BotCommand(command='coffee',description='Варианты кофе')
]