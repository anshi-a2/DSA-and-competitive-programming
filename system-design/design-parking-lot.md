## Reference doc

 - https://www.lldcoding.com/design-lld-a-parking-lot-machine-coding-interview
 - https://www.udemy.com/course/system_design_lld_hld/learn/lecture/41933070#questions/21249962
 - https://www.youtube.com/watch?v=MtjZf7291zc&list=PL6W8uoQQ2c61X_9e6Net0WdYZidm7zooW&index=8
 - https://github.com/AvinashDogiparthi/LowLevelDesign/tree/main/LLDandDesingPatterns/src/C_ParkingLotDesign


## Requirements
1. The parking lot should have multiple levels, each level with a certain number of parking spots.
2. The parking lot should support different types of vehicles, such as cars, motorcycles, and trucks.
3. Each parking spot should be able to accommodate a specific type of vehicle.
4. The system should assign a parking spot to a vehicle upon entry and release it when the vehicle exits.
5. The system should track the availability of parking spots and provide real-time information to customers.
6. The system should handle multiple entry and exit points and support concurrent access.

## Classes, Interfaces and Enumerations
1. The **ParkingLot** class follows the Singleton pattern to ensure only one instance of the parking lot exists. It maintains a list of levels and provides methods to park and unpark vehicles.
2. The **Level** class represents a level in the parking lot and contains a list of parking spots. It handles parking and unparking of vehicles within the level.
3. The **ParkingSpot** class represents an individual parking spot and tracks the availability and the parked vehicle.
4. The **Vehicle** class is an abstract base class for different types of vehicles. It is extended by Car, Motorcycle, and Truck classes.
5. The **VehicleType** enum defines the different types of vehicles supported by the parking lot.
6. Multi-threading is achieved through the use of synchronized keyword on critical sections to ensure thread safety.
7. The **Main** class demonstrates the usage of the parking lot system.

## Design Patterns Used:
1. Singleton Pattern: Ensures only one instance of the ParkingLot class.
2. Factory Pattern (optional extension): Could be used for creating vehicles based on input.
3. Observer Pattern (optional extension): Could notify customers about available spots.


### HLD

<img width="1141" alt="image" src="https://github.com/user-attachments/assets/f2258731-8fae-47ec-bc48-2930c228a2c4" />


<img width="937" alt="image" src="https://github.com/user-attachments/assets/15d351f4-c86d-4ada-8f81-41c3221ad7e4" />


<img width="937" alt="image" src="https://github.com/user-attachments/assets/af8d371b-1efb-4a37-b9de-671c40dced6f" />

<img width="937" alt="image" src="https://github.com/user-attachments/assets/6f41e663-acba-4d30-bd81-7ab17bd762f0" />

<img width="765" alt="image" src="https://github.com/user-attachments/assets/71837ca7-190a-47f4-896a-24129d5a1211" />

<img width="1085" alt="image" src="https://github.com/user-attachments/assets/b5861bde-b50e-4b5c-a3e6-91949dfa13d1" />


<img width="555" alt="image" src="https://github.com/user-attachments/assets/2cb658db-cc98-4169-bcb8-0abf07d80c7f" />


<img width="940" alt="image" src="https://github.com/user-attachments/assets/228c0281-d2b2-42bb-8323-1dbc690f653f" />


<img width="663" alt="image" src="https://github.com/user-attachments/assets/bad569a1-30ca-408a-ac57-449739cfea05" />


<img width="663" alt="image" src="https://github.com/user-attachments/assets/e6f9e565-be43-46c0-b5d7-d7d0ff3504cd" />


<img width="663" alt="image" src="https://github.com/user-attachments/assets/fdaed31e-fc66-415a-9ee1-62cff44e0fc8" />


<img width="915" alt="image" src="https://github.com/user-attachments/assets/92670725-0823-4acf-a9cd-cb51e2b1035d" />


<img width="915" alt="image" src="https://github.com/user-attachments/assets/e793eb28-3369-4222-a59d-a29463a6594f" />




## LLD


## Code design


# Parking Lot System (LLD)

## Problem Statement

Design and implement a Parking Lot Management System that supports parking and unparking of vehicles, ticket generation, fee calculation, and management of multiple floors and spot types.

---

## Requirements

- **Multiple Floors:** The parking lot can have multiple floors.
- **Parking Spots:** Each floor has multiple parking spots of different types (e.g., car, bike, truck).
- **Vehicle Types:** Support for different vehicle types (see `vehicletype/`).
- **Ticketing:** Generate a ticket when a vehicle is parked.
- **Unparking:** Allow vehicles to unpark and calculate the parking fee.
- **Fee Calculation:** Support for different fee strategies (see `fee/`).
- **Spot Allocation:** Allocate the nearest available spot of the correct type.
- **Extensibility:** Easy to add new vehicle types, spot types, or fee strategies.

---

## Core Entities

- **ParkingLot:** Main class managing the entire parking lot, floors, and overall operations.
- **ParkingFloor:** Represents a single floor in the parking lot, manages its spots.
- **ParkingSpot:** Represents an individual parking spot, knows its type and occupancy.
- **Ticket:** Represents a parking ticket issued when a vehicle is parked.
- **VehicleType (in `vehicletype/`):** Enum or classes for different vehicle types.
- **Fee Calculation (in `fee/`):** Classes for calculating parking fees based on duration and vehicle type.

---

## Class Design

### 1. ParkingLot
- **Methods:**
  - `parkVehicle(Vehicle vehicle)`
  - `unparkVehicle(String ticketId)`
  - `addFloor(ParkingFloor floor)`
  - `getAvailableSpots()`
- **Fields:** List of floors, mapping of tickets, etc.

### 2. ParkingFloor
- **Methods:**
  - `getAvailableSpot(VehicleType type)`
  - `parkVehicle(Vehicle vehicle)`
  - `unparkVehicle(String spotId)`
- **Fields:** List of spots, floor number.

### 3. ParkingSpot
- **Methods:**
  - `isAvailable()`
  - `assignVehicle(Vehicle vehicle)`
  - `removeVehicle()`
- **Fields:** Spot ID, type, current vehicle.

### 4. Ticket
- **Fields:** Ticket ID, vehicle info, entry time, spot info.

### 5. VehicleType (in `vehicletype/`)
- Enum or classes for vehicle types (Car, Bike, Truck, etc.)

### 6. Fee Calculation (in `fee/`)
- **Methods:** `calculateFee(Ticket ticket, Date exitTime)`
- **Extensible:** Add new strategies for fee calculation.

---

## Design Patterns Used

- **Strategy Pattern:** For fee calculation strategies.
- **Factory Pattern:** (If used) For creating vehicles or spots.
- **Singleton Pattern:** (If used) For ParkingLot instance.

---

## Example Usage

```java
ParkingLot lot = new ParkingLot();
lot.addFloor(new ParkingFloor(...));
Ticket ticket = lot.parkVehicle(new Car("KA-01-1234"));
lot.unparkVehicle(ticket.getId());
```

---

## Demo

See `ParkingLotDemo.java` for a sample usage of the parking lot system.

---

## Extending the Framework

- **Add a new vehicle type:** Update or add to `vehicletype/`.
- **Add a new fee strategy:** Implement a new class in `fee/`.
- **Add new spot types or floors:** Extend `ParkingSpot` or `ParkingFloor`.

---



### Ticket.java


```java
package parkinglot;

import parkinglot.vehicletype.Vehicle;

import java.util.Date;

public class Ticket {
    private final String ticketId;
    private final Vehicle vehicle;
    private final ParkingSpot spot;
    private final long entryTimestamp;
    private long exitTimestamp;

    public Ticket(String ticketId, Vehicle vehicle, ParkingSpot spot) {
        this.ticketId = ticketId;
        this.vehicle = vehicle;
        this.spot = spot;
        this.entryTimestamp = new Date().getTime();
    }

    public String getTicketId() { return ticketId; }
    public Vehicle getVehicle() { return vehicle; }
    public ParkingSpot getSpot() { return spot; }
    public long getEntryTimestamp() { return entryTimestamp; }
    public long getExitTimestamp() { return exitTimestamp; }

    public void setExitTimestamp() {
        this.exitTimestamp = new Date().getTime();
    }
}
```


### Parking spot.java

```java
package parkinglot;

import parkinglot.vehicletype.Vehicle;
import parkinglot.vehicletype.VehicleType;

public class ParkingSpot {
    private final int spotNumber;
    private final VehicleType vehicleType;
    private Vehicle vehicle;
    private boolean isOccupied;

    public ParkingSpot(int spotNumber, VehicleType vehicleType) {
        this.spotNumber = spotNumber;
        this.vehicleType = vehicleType;
        this.isOccupied = false;
    }

    public synchronized boolean isAvailable() {
        return !isOccupied;
    }

    public synchronized boolean park(Vehicle vehicle) {
        if (isOccupied || vehicle.getType() != vehicleType) {
            return false;
        }
        this.vehicle = vehicle;
        isOccupied = true;
        return true;
    }

    public synchronized void unpark() {
        vehicle = null;
        isOccupied = false;
    }

    public VehicleType getVehicleType() {
        return vehicleType;
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public int getSpotNumber() {
        return spotNumber;
    }
}
```



### ParkingLotDemo.java


```java
package parkinglot;

import parkinglot.fee.VehicleBasedFeeStrategy;
import parkinglot.vehicletype.*;

import java.util.ArrayList;
import java.util.List;

public class ParkingLotDemo {
    public static void run() {
        ParkingLot parkingLot = ParkingLot.getInstance();

        List<ParkingSpot> parkingSpotsFloor1 = List.of(
                new ParkingSpot(101, VehicleType.CAR),
                new ParkingSpot(102, VehicleType.CAR),
                new ParkingSpot(103, VehicleType.BIKE)
        );

        List<ParkingSpot> parkingSpotsFloor2 = List.of(
                new ParkingSpot(201, VehicleType.BIKE),
                new ParkingSpot(202, VehicleType.TRUCK)
        );

        // Add a floor with different types of spots
        ParkingFloor floor1 = new ParkingFloor(1, parkingSpotsFloor1);
        ParkingFloor floor2 = new ParkingFloor(2, parkingSpotsFloor2);

        parkingLot.addFloor(floor1);
        parkingLot.addFloor(floor2);

        parkingLot.setFeeStrategy(new VehicleBasedFeeStrategy());

        // Create vehicles
        Vehicle car1 = new Car("ABC123");
        Vehicle car2 = new Car("XYZ789");
        Vehicle bike1 = new Bike("M1234");

        // View available spots
        System.out.println("Available spots for Car:");
        for (ParkingFloor floor: parkingLot.getParkingFloors()) {
            System.out.println("Floor: " + floor.getFloorNumber() + " " + floor.getAvailableSpots(VehicleType.CAR));
        }

        List<String> parkingTickets = new ArrayList<>();

        // Park vehicles
        try {
            Ticket ticket1 = parkingLot.parkVehicle(car1);
            System.out.println("Car 1 parked: " + ticket1.getTicketId());
            parkingTickets.add(ticket1.getTicketId());

            Ticket ticket2 = parkingLot.parkVehicle(car2);
            System.out.println("Car 2 parked: " + ticket2.getTicketId());
            parkingTickets.add(ticket2.getTicketId());

            Ticket ticket3 = parkingLot.parkVehicle(bike1);
            System.out.println("Bike 1 parked: " + ticket3.getTicketId());
            parkingTickets.add(ticket3.getTicketId());

            // Try parking another car when spots are full
            Vehicle car3 = new Car("DL0432");
            parkingLot.parkVehicle(car3);
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }

        // Unpark vehicles
        try {
            double fee = parkingLot.unparkVehicle(parkingTickets.getFirst()); // valid ticket ID
            System.out.println("Ticket: " + parkingTickets.getFirst() + ", Fee: " + fee);

            fee = parkingLot.unparkVehicle("1"); // invalid ticket ID
        } catch (Exception e) {
            System.out.println("Exception while unparking: " + e.getMessage());
        }
    }
}
```


### Parkinglot.java


```java
package parkinglot;

import parkinglot.fee.FeeStrategy;
import parkinglot.fee.FlatRateFeeStrategy;
import parkinglot.vehicletype.Vehicle;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ParkingLot {
    private static ParkingLot instance;
    private final List<ParkingFloor> floors;
    private final Map<String, Ticket> activeTickets = new ConcurrentHashMap<>();
    private FeeStrategy feeStrategy;

    private ParkingLot() {
        floors = new ArrayList<>();
        feeStrategy = new FlatRateFeeStrategy();
    }

    public static synchronized ParkingLot getInstance() {
        if (instance == null) {
            instance = new ParkingLot();
        }
        return instance;
    }

    public void addFloor(ParkingFloor floor) {
        floors.add(floor);
    }

    public void setFeeStrategy (FeeStrategy feeStrategy) {
        this.feeStrategy = feeStrategy;
    }

    public synchronized Ticket parkVehicle(Vehicle vehicle) throws Exception {
        for (ParkingFloor floor : floors) {
            Optional<ParkingSpot> spotOpt = floor.getAvailableSpot(vehicle.getType());
            if (spotOpt.isPresent()) {
                ParkingSpot spot = spotOpt.get();
                if (spot.park(vehicle)) {
                    String ticketId = UUID.randomUUID().toString();
                    Ticket ticket = new Ticket(ticketId, vehicle, spot);
                    activeTickets.put(ticketId, ticket);
                    return ticket;
                }
            }
        }
        throw new Exception("No available spot for " + vehicle.getType());
    }

    public synchronized double unparkVehicle(String ticketId) throws Exception {
        Ticket ticket = activeTickets.remove(ticketId);
        if (ticket == null) throw new Exception("Invalid ticket");

        ParkingSpot spot = ticket.getSpot();
        spot.unpark();

        ticket.setExitTimestamp();
        return feeStrategy.calculateFee(ticket);
    }

    public List<ParkingFloor> getParkingFloors() {
        return floors;
    }
}
```


### ParkingFloor.java


```java
package parkinglot;

import parkinglot.vehicletype.VehicleType;

import java.util.List;
import java.util.Optional;

public class ParkingFloor {
    private final int floorNumber;
    private final List<ParkingSpot> parkingSpots;

    public ParkingFloor(int floorNumber, List<ParkingSpot> spots) {
        this.floorNumber = floorNumber;
        this.parkingSpots = spots;
    }

    public synchronized Optional<ParkingSpot> getAvailableSpot(VehicleType type) {
        return parkingSpots.stream()
                .filter(spot -> spot.isAvailable() && spot.getVehicleType() == type)
                .findFirst();
    }

    public int getFloorNumber() { return floorNumber; }

    public List<ParkingSpot> getParkingSpots() {
        return parkingSpots;
    }

    public List<Integer> getAvailableSpots(VehicleType type) {
        return parkingSpots.stream()
                .filter(spot -> spot.isAvailable() && spot.getVehicleType() == type)
                .map(ParkingSpot::getSpotNumber)
                .toList();
    }
}
```



### vehicleType

### Bike.java

```java
package parkinglot.vehicletype;

public class Bike extends Vehicle {
    public Bike(String license) {
        super(license, VehicleType.BIKE);
    }
}
```


### car.java

```java
package parkinglot.vehicletype;

public class Car extends Vehicle {
    public Car(String license) {
        super(license, VehicleType.CAR);
    }
}
```


### vehicle.java

```java
package parkinglot.vehicletype;

public abstract class Vehicle {
    protected String licensePlate;
    protected VehicleType type;

    public Vehicle(String licensePlate, VehicleType type) {
        this.licensePlate = licensePlate;
        this.type = type;
    }

    public String getLicensePlate() { return licensePlate; }
    public VehicleType getType() {
        return type;
    }
}
```




### vehicleType.java


```java
package parkinglot.vehicletype;

public enum VehicleType {
    CAR,
    BIKE,
    TRUCK
}
```


### fee

### feeStrategy.java

```java
package parkinglot.fee;

import parkinglot.Ticket;

public interface FeeStrategy {
    double calculateFee(Ticket ticket);
}
```


### faltRateFeeStrategy.java

```java
package parkinglot.fee;

import parkinglot.Ticket;

public class FlatRateFeeStrategy implements FeeStrategy {

    private static final double RATE_PER_HOUR = 10.0;

    @Override
    public double calculateFee(Ticket ticket) {
        long duration = ticket.getExitTimestamp() - ticket.getEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * RATE_PER_HOUR;
    }
}
```


### vehicleBasedFeeStrategy.java


```java
package parkinglot.fee;

import parkinglot.Ticket;
import parkinglot.vehicletype.VehicleType;

import java.util.Map;

public class VehicleBasedFeeStrategy implements FeeStrategy {
    private final Map<VehicleType, Double> hourlyRates = Map.of(
            VehicleType.CAR, 20.0,
            VehicleType.BIKE, 10.0,
            VehicleType.TRUCK, 30.0
    );

    @Override
    public double calculateFee(Ticket ticket) {
        long duration = ticket.getExitTimestamp() - ticket.getEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * hourlyRates.get(ticket.getVehicle().getType());
    }
}
```
