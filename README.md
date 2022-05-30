# Генерация трехмерного ландшафта методом шума Перлина

## Описание идеи: 
Разработать программное обеспечение, выполняющее генерацию и визуализацию сцены,
представляющей трехмерный ландшафт. В основу генерации положить шум Перлина.

## Описание предметной области:
Создание процедурно трехмерного ландшафта. Пользователь в интерфейсе может изменять настройки генерации сцены как вручную, так и при пмощи загрузки файла. 

## Анализ аналогичных решений
| Решение        | Критерии     |              |                |
|:--------------:|:------------:|:------------:|:--------------:|
|                | OpenSource   |Порог входа   |Реалистичность  |
| UnrealEngine   |       &#177; |    Высокий   |  1             |
| Unity          |       &#177; |  Высокий     |   2            |
| Godot          |       +      |    Средний   |      3         | 

У таких технологий как UnrealEngine и Unity бесплатное использование продукта, пока доход компании не превысит определенную сумму.

Сравнение реалистичности представлена оценкой, где 1 -- наилучшая из представленных.

## Актуальность и целесообразность проекта
Импортозамещение

## Use-Case диаграмма
![](images/use-case.svg)

## ER-диаграмма сущностей
![](images/er-model.svg)

## Архитектурные харастеристики
В качестве архитектурного паттерна используется MVC.

Приложение содержит монолитную архитектуру.

## Технологический стек приложения
Данный проект представляет собой Desktop-приложение. Его реализация выполняется при помощи использования следующих частей: 

1. Язык программирования &ndash; C++ в качестве основного языка. Использование фреймворка QT (Qt5).
2. Хранилище данных:
    
    * обычный файл формата .txt;
    * обычный файл формата .bmp;
    * СУБД PostgreSQL и MySQL для хранения пользователей.
3. Unit-тестирование: использование Gtest.

## Диаграмма компонентов
![](images/components.svg)

## Диаграмма классов компонента доступа к данным
![](images/data_access.svg)

## Диаграмма классов компонента бизнес-логики
![](images/business_logic.svg)

## Диаграмма «модельных» классов сущности базы данных
![](images/model_data_access.svg)

## Диаграмма «модельных» классов сущности системы.
![](images/model_business.svg)

## Диаграмма «модельных» классов транспортной сущности.
![](images/model_transport.svg)

## Диаграмма классов для MVC
![](images/mvc.svg)

## Диаграмма классов для технологического UI
![](images/techno_ui.svg)

## Диаграмма классов единого приложения
![](images/all_app.svg)

