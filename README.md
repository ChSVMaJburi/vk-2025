# MetricsLibrary

Простой и легко масштабируемый C++20 набор для сбора и записи метрик в текстовый файл.

## Файлы
```
include/metrics/
  IMetric.h        # Интерфейс метрик
  Counter.h        # Счётчик целых значений
  Gauge.h          # Среднее по вещественным
  CurrentTime.h    # Время в ISO
  Writer.h         # Запись в файл
  MetricsManager.h # Регистрация и запись
src/
  *.cpp            # Реализация
test_main.cpp      # Пример использования
CMakeLists.txt     # Сборка проекта
README.md          # Вы этот файл
```

## Сборка и запуск
```
mkdir build && cd build
cmake ..
make
./test_metrics
```