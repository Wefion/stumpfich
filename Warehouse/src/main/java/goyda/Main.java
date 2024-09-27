package goyda;
import java.awt.image.AreaAveragingScaleFilter;
import java.util.ArrayList;

enum States{
    EXPECTED,    // ожидается
    PROCESSING,  // обрабатывается
    SENDING      // отправляется
}

// Класс, который создаёт заказы, работников, склад и вызывает доставку
class Order {
    String receiverAddress = null; // Адрес получателя
    String vendor = null; // Поставщик
    String prodName = null; // Название товара
    String prodDesc = null; // Описание товара
    int prodCost = -1; // Цена товара
    int prodId = -1; //  id товара
    States status; // Статус товара

    // Полный конструктор
    Order(String receiverAddress, String prodName, String vendor, String prodDesc, int prodCost, int prodId) {
        System.out.println("Создан заказ");
        this.receiverAddress = receiverAddress;
        this.prodName = prodName;
        this.vendor = vendor;
        this.prodDesc = prodDesc;
        this.prodCost = prodCost;
        this.prodId = prodId;
    }
    Order(){}

    void info(){
        System.out.println("Название товара: " + prodName + "\n" + "Описание товара: " + prodDesc + "\n" +
                "Цена товара: " + prodCost + "\n" + "ID товара: " + prodId + "\n" + "Поставщик товара: " + vendor +
                "\n");
    }
}



// Класс склада
class Warehouse{
    // Список заказов - для каждого работника он один
    static ArrayList<Order> queueList = new ArrayList<>();

    Delivery del = new Delivery();

    // Добавить товар в очередь
    void addOrder(Order order){
        // Добавить товар в очередь и отметить его статус
        queueList.add(order);
        order.status = States.PROCESSING;
    }

    // Один работник может обрабатывать один заказ одновременно
    synchronized void processOrder(){
        System.out.println("["+Thread.currentThread().getName() + "]" + " обрабатывает заказ...");

        // Проверяем заказ на подлинность(совпадают все характеристики)
        boolean isCorrect = (queueList.getLast().prodName != null || queueList.getLast().receiverAddress != null
        || queueList.getLast().vendor != null || queueList.getLast().prodDesc != null
        || queueList.getLast().prodCost != -1 || queueList.getLast().prodId != -1);

        // Если всё совпадает - товар валиден, можно передавать в доставку
        if (isCorrect) {
            System.out.println("Товар " + queueList.getLast().prodName + " найден и скоро будет передан в доставку!");
            queueList.getLast().status = States.PROCESSING;

            // Отправляем заказ в доставку и освобождаем его из списка заказов
            del.getOrder(queueList.getLast());
            queueList.removeLast();
        } else {
            System.out.println("Товар " + queueList.getLast().prodName + " не найден в системе, отправляем обратно на склад поставщику!");
            queueList.getLast().status = States.EXPECTED;
            queueList.removeLast();
        }
        System.out.println("["+Thread.currentThread().getName() + "]" + "выполнил свою работу");
    }
}


class Worker implements Runnable{
    Thread t; // Поток в рабочем
    Warehouse wh; //Рабочий имеет доступ ко складу
    static int numOfWorker = 0; // Номер рабочего

    // Создание рабочего для склада

    Worker(Warehouse wh){
        this.wh = wh;
        t = new Thread(this,"Работник " + numOfWorker);
        numOfWorker++;
    }
    
    public void run(){
        wh.processOrder();
    }
}


class Delivery implements Runnable{
    ArrayList<Order> pack = new ArrayList<>();
    Thread t;

    Delivery(){
        t = new Thread(this, "додо пицца доставка");
    }

    void getOrder(Order order){
        try {
            // Пусть каждый работник может относить только 2 товара одновременно
            if (pack.size() > 2) {
                Thread.currentThread().wait();
                System.out.println("Эээ биля куда лезешь, не видишь доставка работает жиес? поспи епта");

                // Усыпляет работника за то, что много на себя взял
                Thread.sleep(1000);
                
            }
            pack.add(order);
        }catch (InterruptedException e){
            System.out.println("ЕБЛАН?");
        }
    }
    public void run(){

    }
}

// В будующем будет
class Monitor{

}

class Simulation{
    private Order obj = new Order();
    private Order chocolate = new Order(
            "New Goya, GoyaSt 148c",
            "milk chocolate with cobnut",
            "Millz",
            "The combination of milk chocolate and whole hazelnuts is a delicious duo," +
                    "the taste of which is unlikely to leave anyone indifferent.It tastes better when it's more tender!",
            150,
            1
    );

    private Order laptop = new Order(
            "123 Elm Street, Apartment 45",
            "Gaming Laptop",
            "TechCorp",
            "A powerful gaming laptop with 16GB RAM, 1TB SSD, and RTX 3080 GPU for an immersive gaming experience.",
            1500,
            2
    );

    private Order book = new Order(
            "456 Maple Avenue, House 23",
            "Java Programming Guide",
            "BookWorld",
            "A comprehensive Guide to mastering Java programming with examples and best practices.",
            45,
            3
    );

    private Order phone = new Order(
            "789 Oak Street, Office 12",
            "Smartphone XL",
            "PhoneWorld",
            "Latest model smartphone with a 6.5-inch display, 128GB storage, and 5G connectivity.",
            999,
            4
    );

    private Order headphones = new Order(
            "101 Pine Road, Building 7",
            "Wireless Headphones",
            "AudioTech",
            "Noise-cancelling wireless headphones with long battery life and high-facibility sound quality.",
            200,
            5
    );

    void startSimulation(){
        // Добавить товары в список
        Warehouse wh = new Warehouse();

        wh.addOrder(obj);
        wh.addOrder(chocolate);
        wh.addOrder(laptop);
        wh.addOrder(book);
        wh.addOrder(phone);
        wh.addOrder(headphones);

        //Соси хуй
        Worker w1 = new Worker(wh);
        Worker w2 = new Worker(wh);
        Worker w3 = new Worker(wh);
        Worker w4 = new Worker(wh);
        Worker w5 = new Worker(wh);
        Worker w6 = new Worker(wh);

        w1.t.start();
        w2.t.start();
        w3.t.start();
        w4.t.start();
        w5.t.start();
        w6.t.start();

        try{
            w1.t.join();
            w2.t.join();
            w3.t.join();
            w4.t.join();
            w5.t.join();
            w6.t.join();
        }catch (InterruptedException e){
            System.out.println("Главный поток прерван.");
        }
    }
}


public class Main {
    public static void main(String[] args) {
        Simulation s = new Simulation();
        s.startSimulation();
    }
}