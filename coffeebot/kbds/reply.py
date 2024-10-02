'''from aiogram.types import ReplyKeyboardMarkup, KeyboardButton, ReplyKeyboardRemove, KeyboardButtonPollType
from aiogram.utils.keyboard import ReplyKeyboardBuilder

# Создание клавиатуры
start_kb = ReplyKeyboardMarkup(
    keyboard=[
        [
            KeyboardButton(text="Меню"),
            KeyboardButton(text="О магазине"),
        ],
        {
            KeyboardButton(text="Варианты доставки"),
            KeyboardButton(text="Варианты оплаты"),
        }
    ],
    resize_keyboard = True, # Поменять размер клавиатуры
    input_field_placeholder = "Что вас интересует?" # Сообщение, выводимое в строке ввода 
)
del_kbd = ReplyKeyboardRemove() # Удаление клавиатуры


# Новая клавиатура, используя ReplyKeyboardBuilder
start_kb2 = ReplyKeyboardBuilder()
start_kb2.add(
    KeyboardButton(text = "О магазине"),
    KeyboardButton(text = "Варианты доставки"),
    KeyboardButton(text = "Варианты оплаты"),
)
start_kb2.adjust(2,2)


# Новая клавиатура, которая  собирается из второй и добавляет новую кнопку
# а так же показывает старые (2 кнопки и 2 ряда) через adjust
start_kb3 = ReplyKeyboardBuilder()
start_kb3.attach(start_kb2)
start_kb3.add(KeyboardButton(text = "Список кофе на выбор: "))
start_kb3.adjust(2,2)

# Тест клавиатуры метки
test_kb = ReplyKeyboardMarkup(
    keyboard = [
        [
            KeyboardButton(text = "Создать опрос", request_poll = KeyboardButtonPollType()),
        ],
        [
            KeyboardButton(text = "Отправить номер ☎️", request_contact = True),
            KeyboardButton(text = "Отправить локацию 🗺️", request_location = True),
        ],
    ],
    resize_keyboard = True,
)

# Кофе клавиатура
coffee_kb = ReplyKeyboardBuilder()
coffee_kb.add(
    KeyboardButton(text="Латте"),
    KeyboardButton(text="Капучино"),
    KeyboardButton(text="Американо"),
    KeyboardButton(text="Дип"),
    KeyboardButton(text="Раф"),
    KeyboardButton(text="Понос(ultrarare!)"),
)
coffee_kb.adjust(2,2,2)'''

from aiogram.types import KeyboardButton
from aiogram.utils.keyboard import ReplyKeyboardBuilder


def get_keyboard(
    *btns: str,
    placeholder: str = None,
    request_contact: int = None,
    request_location: int = None,
    sizes: tuple[int] = (2,),
):
    '''
    Parameters request_contact and request_location must be as indexes of btns args for buttons you need.
    Example:
    get_keyboard(
            "Меню",
            "О магазине",
            "Варианты оплаты",
            "Варианты доставки",
            "Отправить номер телефона"
            placeholder="Что вас интересует?",
            request_contact=4,
            sizes=(2, 2, 1)
        )
    '''
    keyboard = ReplyKeyboardBuilder()

    for index, text in enumerate(btns, start=0):
        
        if request_contact and request_contact == index:
            keyboard.add(KeyboardButton(text=text, request_contact=True))

        elif request_location and request_location == index:
            keyboard.add(KeyboardButton(text=text, request_location=True))
        else:

            keyboard.add(KeyboardButton(text=text))

    return keyboard.adjust(*sizes).as_markup(
            resize_keyboard=True, input_field_placeholder=placeholder)
