from aiogram import F, types, Router
from aiogram.enums import ParseMode
from aiogram.filters import Command, CommandStart, or_f
from aiogram.utils.formatting import as_list, as_marked_section, Bold, Italic


from filters.chat_types import ChatTypeFilter

from kbds import reply

# создаём роутер
user_private_router = Router()
user_private_router.message.filter(ChatTypeFilter(["private"]))

# благодаря хендлерам бот будет знать, как отвечать на сообщения пользователя
# после сообщения передаём клавиатуру боту из reply
@user_private_router.message(CommandStart())
async def start_cmd(message: types.Message):
    await message.answer(
        "Привет, я кофейный бот!",
         reply_markup= reply.get_keyboard(
             "Меню",
             "О магазине",
             "Варианты оплаты",
             "Варианты доставки",
             placeholder= "Что вас интересует?",
             sizes=(2, 2)
         ),
    )


# ответ на сообщение "кофе" или команду /menu
@user_private_router.message(or_f(Command("menu"),(F.text.lower().contains("меню"))))
async def coffee_cmd(message:types.Message):
    await message.answer(
        "Выберите кофе: ",
        reply_markup=reply.get_keyboard(
            "Латте","Мокка","Классический",
            "Экспрессо", "Доппио", "Американо",
            "Раф", "Гляссе", "Капучино",
            placeholder= "Выберите кофе",
            sizes=(3,3,3,)
        ),
    )


# ответ на сообщение "о нас" или команду /about
@user_private_router.message(or_f(Command("about"),(F.text.lower().contains("о магазине"))))
async def about_cmd(message: types.Message):
    await message.answer("О нас: ")


# ответ на сообщение "оплата" или команду /payment
@user_private_router.message(or_f(Command("payment"),(F.text.lower().contains("оплат"))))
async def payment_cmd(message: types.Message):
    text = as_marked_section(
        Bold("Варианты оплаты: "),
        "Картой в боте",
        "При получении карта/кеш",
        "В заведении",
        marker= '✅ '
    )
    await message.answer(text.as_html())


# ответ на сообщение "доставка" или команду /shipping
@user_private_router.message(or_f(Command("shipping"),(F.text.lower().contains("доставк"))))
async def shipping_cmd(message: types.Message):
    text = as_list(
        as_marked_section(
            Bold("Варианты доставки/заказа: "),
            "Шнырь-курьер",
            "Самовынос (притянул теперь моё)",
            "Похаваю у вас(а чё бы и нет)",
            marker='✅ '
        ),
        as_marked_section(
            Bold("Нельзя:"),
            "Почта",
            "Голуби",
            marker= '❌ '
        ),
        sep="\n----------------------\n"
    )
    await message.answer(text.as_html())





# отправляет номер
@user_private_router.message(F.contact)
async def get_contact(message: types.Message):
    await message.answer(f"номер получен")
    await message.answer(str(message.contact))

# отправляет локацию
@user_private_router.message(F.location)
async def get_contact(message: types.Message):
    await message.answer(f"локация получена")
    await message.answer(str(message.location))



# ЙОУ
@user_private_router.message(F.text)
async def what_cmd(message: types.Message):
    await message.answer(message.text)