cmake_minimum_required(VERSION 3.28)
project(FileUtilsV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(FileUtilsV2 main.c
        src/core/User.database.c
        src/core/User.database.h
        System.c
        System.h
        src/cli/UserCommand.c
        src/cli/UserCommand.h
        src/core/Order.database.c
        src/core/Order.database.h
        src/utils/CheckToken.c
        src/utils/CheckToken.h
        src/cli/OrderCommand.c
        src/cli/OrderCommand.h
        src/cli/OrderRoomCommand.c
        src/cli/OrderRoomCommand.h
        src/core/OrderRoom.c
        src/core/OrderRoom.h
        src/cli/OrderRoomCommand.c
        src/cli/OrderRoomCommand.h
        src/utils/generateUUID.c
        src/utils/generateUUID.h
        src/core/Staff.database.c
        src/core/Staff.database.h
        src/core/OrderService.c
        src/core/OrderService.h
        src/utils/FetchUsernameFromTokenFile.c
        src/utils/FetchUsernameFromTokenFile.h
        src/utils/ShowUserOrder.c
        src/utils/ShowUserOrder.h
        src/cli/OrderServiceCommand.c
        src/cli/OrderServiceCommand.h
        src/core/Room.database.c
        src/core/Room.database.h
        src/utils/Date.c
        src/utils/Date.h
        src/core/Service.database.c
        src/core/Service.database.h
        src/cli/ServiceCLI.c
        src/cli/ServiceCLI.h
        src/cli/StaffCommand.c
        src/cli/StaffCommand.h
        src/cli/RoomCommand.c
        src/cli/RoomCommand.h
        src/utils/readFromFile.c
        src/utils/readFromFile.h
)
