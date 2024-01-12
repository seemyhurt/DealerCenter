<!DOCTYPE html>
<html>
<head>
 <meta charset="UTF-8">
</head>
<body>
 <h1>Добро пожаловать в систему управления дилерским центром!</h1>
 <p>На данной странице представлено руководство пользователя данным программным обеспечением.</p>

 <h2>Интерфейс покупателя</h2>
 <p>В режиме покупателя для Вас открывается возможность использовать данное программное обеспечение для совершения покупок транспортных средств.<br>
    Транспортные средства выбираются из ограниченного списка моделей, которые имеются в наличиии на данный момент.<br>
    Цена на транспортное средство зависит от закупочной цены, времени доставки и года выпуска автомобиля.<br>
    Если Вы хотите использовать данное программное обеспечение как покупатель, то Вам необходимо нажать на соответствующий пункт "Customer" в контекстном меню "Interface".<br>
    Если ранее Вы уже производили регистрацию, то Вы можете ввести предыдущую комбинацию логина и пароля.<br>
    Вам отобразятся предыдущие совершенные покупки и будет доступен весь функционал покупателя.<br>
    Если же Вы - новый пользователь, то необходимо нажать соответствующую кнопку "New user" в диалоговом окне входа.<br>
    Для регистрации необходимо будет ввести следующие поля:</p>
 <ul>
  <li>Phone number – Ваш персональный номер телефона. Должен содержать 11 символов и начинаться с цифры 8;</li>
  <li>Last name - Ваша фамилия, должна начинаться с большой буквы и быть не более 30 символов длиной;</li>
  <li>First name - Ваше имя, должно начинаться с большой буквы и быть не более 30 символов длиной;</li>
  <li>Patronymic - Ваше отчество, должно начинаться с большой буквы и быть не более 30 символов длиной, но может отсутствовать;</li>
  <li>Age - Ваш возраст, целое число в диапазоне от 1 до 100;</li>
  <li>Password - Ваш пароль, который Вы планируете использовать для входа в систему, может содержать любой набор цифр и букв.</li>
 </ul>

 <h2>Интерфейс менеджера</h2>
 <p>В режиме менеджера для Вас открывается возможность использовать данное программное обеспечение для совершения закупок транспортных средств от производителя.<br>
    Возможные для закупки бренды и типы транспортных средств определяются имеющимися поставщиками для данного центра.<br>
    Поставщик предлагает единственный тип и бренд транспортного средства, при этом он может поставить любую модель транспортного средства любого года выпуска и состояния.<br>
    Цена на транспортное средство зависит от закупочной цены, которую установил производитель.<br>
    Если Вы хотите использовать данное программное обеспечение как менеджер, то Вам необходимо нажать на соответствующий пункт "Manager" в контекстном меню "Interface".<br>
    Пользователей, которые могут использовать данное программное обеспечение как менеджер регистрирует администратор центра, поэтому для регистрации Вам необходимо<br>
    использовать номер телефона и пароль, который установил администратор.</p>

<h2>Интерфейс администратора</h2>
<p>При первом запуске приложения необходимо будет зарегестрировать пользователя, который будет выполнять роль администратора данного приложения.<br>
    Требования к данным администратора (как и менеджера) предъявляются такие же, как было описано в разделе для покупателей.<br>
    Администратор дилерского центра может быть только один, новое добавление администратора возможно только при полной очистке данных.<br>
    Для перехода в режим администратора, необходимо нажать на соответствующий пункт "Administrator" в контекстном меню "Interface".<br>
    Для администратора открывается возможность просматривать все данные, которые доступны для текущей версии приложения: данные о производителях,<br>
    данные о менеджерах, о покупателях и о наличии транспортных средств. А также добавлять поставщиков транспортных средств и менеджеров приложения.<br>
    Для регистрации нового поставщика необходимо ввести следующие поля:</p>
<ul>
    <li>Name – Название поставщика, должно начинаться с большой буквы и быть не более 30 символов длиной, имя должно быть уникальным;</li>
    <li>Delivery time, days - время доставки в днях, за которое производитель доставляет транспортное средства до цента, может принимать значения от 1 до 100;</li>
    <li>Guarantee period, years - период гарантии, которой предоставляет производитель на свои транспортные средства, может принимать значения от 1 до 10;</li>
    <li>Transport brand - брэнд поставляемых транспортных средств, должен начинаться с большой буквы и быть не более 30 символов длиной;</li>
    <li>Transport type - тип поставляемых транспортных средств, должно начинаться с большой буквы и быть не более 30 символов длиной;</li>
    <li>Base price - закупочная цена для транспортных средств, которые поставляет производитель, может принимать значения от 1 до 999999999.</li>
</ul>
</body>
</html>