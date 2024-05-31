# DHCPv4C HAL Documentation

## Acronyms

- `DHCP`: Dynamic Host Configuration Protocol
- `HAL`: Hardware Abstraction Layer
- `API`: Application Programming Interface
- `IANA`: Internet Assigned Numbers Authority
- `DHCPC`: DHCP Client
- `DHCPV4`: DHCP Version 4
- `IP`: Internet Protocol

## Description

The DHCPv4 HAL (Hardware Abstraction Layer) module provides a standardized interface for interacting with DHCPv4 (Dynamic Host Configuration Protocol version 4) clients and servers within the Reference Design Kit (RDK) ecosystem. It simplifies network configuration by abstracting the complexities of the underlying DHCPv4 protocol.

### DHCPv4 Client Functionality (`dhcp4cApi.h`)

- **Initialization and Configuration:**
      * Start, stop, and configure DHCPv4 client instances.
- **Lease Management:**
      * Acquire, renew, and release IP addresses and network configuration parameters.
- **Event Notifications:**
      * Receive notifications about lease events (acquisition, renewal, expiration).
- **Parameter Retrieval:**
      * Get information about the current lease (IP address, subnet mask, gateway, DNS servers).

### DHCPv4 Server Functionality (`dhcpv4c_api.h`)

- **Initialization and Configuration:**
      * Start, stop, and configure DHCPv4 server instances.
- **Lease Management:**
      * Manage the allocation of IP addresses and network parameters to clients.
- **Client Information Retrieval:**
      * Get information about connected clients (MAC addresses, assigned IP addresses).
  
#### Benefits

- **Simplified Development:** Abstracts the DHCPv4 protocol, making network application development easier.
- **Seamless Integration:** Enables easy integration of DHCPv4 client and server capabilities into RDK devices.
- **Dynamic Configuration:** Allows applications to dynamically obtain and manage network configurations.
  
By providing this abstraction layer, the DHCPv4 HAL module streamlines network configuration management in RDK devices, enabling them to dynamically obtain necessary network parameters and seamlessly participate in DHCPv4-enabled networks.

The diagram below describes a high-level software architecture of the DHCPv4C HAL module stack.

````mermaid
flowchart
    Caller <--> HALIF[HAL Interface - dhcp4cApi.h\n`HAL IF Specifcation / Contract Requirement`]
    HALIF <--> VendorWrapper[HAL dhcp.c/dhcp.cpp\nVendor Implementation]
    VendorWrapper <--> VendorDrivers[Drivers\nVendor Implementation]

````

DHCPv4C HAL is an abstraction layer, implemented to interact with the underlying software through a standard set of APIs to get offered lease time, remaining lease time, remaining time to renew, DHCP State etc.

## Component Runtime Execution Requirements

### Initialization and Startup

The DHCPv4 Client HAL implementation dynamically selects between open-source and proprietary DHCPv4c APIs based on the value of the `UDHCPEnable_v2` configuration parameter.

If `UDHCPEnable_v2` is true, the HAL will utilize open-source dhcpv4c APIs.
If `UDHCPEnable_v2` is false, the HAL will utilize proprietary dhcpv4c APIs.

**Implementation Notes for Vendors:**

- **Hardware Readiness:** Ensure the HAL waits for the underlying network hardware to be ready before initiating any DHCP operations. This might involve checking for a valid network interface and link status.

- **Error Handling:** Implement robust error handling to manage cases where the UDHCPEnable_v2 parameter is not set, invalid, or inaccessible.

3rd party vendors will implement appropriately to meet operational requirements. This interface is expected to block if the hardware is not ready.

## Threading Model

This interface is not required to be thread safe.

Any module which is invoking the API should ensure calls are made in a thread safe manner.

Vendors may implement internal threading and event mechanisms to meet their operational requirements. These mechanisms must be designed to ensure thread safety when interacting with HAL interface. Proper cleanup of allocated resources (e.g., memory, file handles, threads) is mandatory when the vendor software terminates or closes its connection to the HAL.

## Process Model

All APIs are expected to be called from multiple processes. Due to this concurrent access, vendors must implement protection mechanisms within their API implementations to handle multiple processes calling the same API simultaneously. This is crucial to ensure data integrity, prevent race conditions, and maintain the overall stability and reliability of the system.

## Memory Model

- Modules must allocate and de-allocate memory for their internal operations, ensuring efficient resource management.
- Modules are required to release all internally allocated memory upon closure to prevent resource leaks.
- All module implementations and caller code must strictly adhere to these memory management requirements for optimal performance and system stability. Unless otherwise stated specifically in the API documentation.
- All strings used in this module must be zero-terminated. This ensures that string functions can accurately determine the length of the string and prevents buffer overflows when manipulating strings.
  
TODO: Memory Footprint Requirement:

The total memory footprint of the DHCPv4 client module, including:

- Internal data structures
- Memory used by public APIs
- Any allocations made by third-party implementations
- e.g. ...should not exceed 512 KB.

## Power Management Requirements

The HAL is not involved in any of the power management operation.

## Asynchronous Notification Model

There are no asynchronous notifications.

## Blocking calls

- **Synchronous and Responsive:** All APIs within this module should operate synchronously and complete within a reasonable timeframe based on the complexity of the operation. Specific timeout values or guidelines may be documented for individual API calls.

- **Timeout Handling:** To ensure resilience in cases of unresponsiveness, implement appropriate timeouts for API calls where failure due to lack of response is a possibility. Refer to the API documentation for recommended timeout values per function.

- **Non-Blocking Requirement:** Given the single-threaded environment in which these APIs will be called, it is imperative that they do not block or suspend execution of the main thread. Implementations must avoid long-running operations or utilize asynchronous mechanisms where necessary to maintain responsiveness.

TODO: Timeouts

1. Review the DHCPv4 HAL specification to determine the appropriate timeout for internal memory deallocation by third-party vendors.
2. Explicitly state this timeout requirement in the Memory Model documentation.

## Internal Error Handling

- **Synchronous Error Handling:** All APIs must return errors synchronously as a return value. This ensures immediate notification of errors to the caller.
- **Internal Error Reporting:** The HAL is responsible for reporting any internal system errors (e.g., out-of-memory conditions) through the return value.
- **Focus on Logging for Errors:** For system errors, the HAL should prioritize logging the error details for further investigation and resolution.

## Persistence Model

There is no requirement for HAL to persist any setting information.

## Nonfunctional requirements

Following non functional requirement should be supported by the component.

## Logging and debugging requirements

The component should log all the error and critical informative messages, preferably using syslog, printf which helps to debug/triage the issues and understand the functional flow of the system.

The logging should be consistent across all HAL components.

The component is required to record all errors and critical informative messages to aid in identifying, debugging, and understanding the functional flow of the system. Logging should be implemented using the `syslog` method, as it provides robust logging capabilities suited for system-level software. The use of `printf` is discouraged unless syslog is not available.

All HAL components must adhere to a consistent logging process. When logging is necessary, it should be performed into the `dhcp_vendor_hal.log` file, which is located in either the `/var/tmp/` or `/rdklogs/logs/` directories.

Logs must be categorized according to the following log levels, as defined by the Linux standard logging system, listed here in descending order of severity:

- **FATAL:** Critical conditions, typically indicating system crashes or severe failures that require immediate attention.
- **ERROR:** Non-fatal error conditions that nonetheless significantly impede normal operation.
- **WARNING:** Potentially harmful situations that do not yet represent errors.
- **NOTICE:** Important but not error-level events.
- **INFO:** General informational messages that highlight system operations.
- **DEBUG:** Detailed information typically useful only when diagnosing problems.
- **TRACE:** Very fine-grained logging to trace the internal flow of the system.
  
Each log entry should include a timestamp, the log level, and a message describing the event or condition. This standard format will facilitate easier parsing and analysis of log files across different vendors and components.

## Memory and performance requirements

The component should be designed for efficiency, minimizing its impact on system resources during normal operation. Resource utilization (e.g., CPU, memory) should be proportional to the specific task being performed and align with any performance expectations documented in the API specifications.

## Quality Control

To ensure the highest quality and reliability, it is strongly recommended that third-party quality assurance tools like `Coverity`, `Black Duck`, and `Valgrind` be employed to thoroughly analyze the implementation. The goal is to detect and resolve potential issues such as memory leaks, memory corruption, or other defects before deployment.

Furthermore, both the HAL wrapper and any third-party software interacting with it must prioritize robust memory management practices. This includes meticulous allocation, deallocation, and error handling to guarantee a stable and leak-free operation.

## Licensing

The implementation is expected to released under the Apache License 2.0.

## Build Requirements

The source code should be capable of, but not be limited to, building under the Yocto distribution environment. The recipe should deliver a shared library named as `libapi_dhcpv4c.so`

## Variability Management

Changes to the interface will be controlled by versioning, vendors will be expected to implement to a fixed version of the interface, and based on SLA agreements move to later versions as demand requires.

Each API interface will be versioned using [Semantic Versioning 2.0.0](https://semver.org/), the vendor code will comply with a specific version of the interface.

## DHCPv4C or Product Customization

None

## Interface API Documentation

All HAL function prototypes and datatype definitions are available in `dhcp4cApi.h`, `dhcpv4c_api.h` files.

1. Components/Process must include `dhcp4cApi.h`, `dhcpv4c_api.h` to make use of DHCPv4C hal capabilities.
2. Components/Process should add linker dependency for `libapi_dhcpv4c.so`

## Theory of operation and key concepts

### DHCPv4 HAL Interface: Object Lifecycles, Method Sequencing, and State-Dependent Behavior

#### Object Lifecycles

| Component | Creation                | Usage                                       | Destruction          | Unique Identifier  |
| --------- | ----------------------- | ------------------------------------------- | -------------------- | ------------------ |
| Client    | `dhcp4c_init()` returns `dhcp4c_ctx_t`         | `dhcp4c_ctx_t` handle passed to functions    | `dhcp4c_deinit()`      | `dhcp4c_ctx_t` handle |
| Server    | `dhcpv4c_srv_start()`     | Functions operate on client MAC addresses  | `dhcpv4c_srv_stop()`   | No explicit handle, client MAC used |

#### Method Sequencing

| Component | Initialization (Mandatory) | General Order                                    |
| --------- | ---------------------------- | ------------------------------------------------ |
| Client    | `dhcp4c_init()`                | 1. `dhcp4c_set_params()` (optional)               |
|           |                              | 2. `dhcp4c_start()`                               |
|           |                              | 3. Lease operations                             |
|           |                              | 4. `dhcp4c_stop()`                                |
|           |                              | 5. `dhcp4c_deinit()`                              |
| Server    | `dhcpv4c_srv_start()`          | 1. `dhcpv4c_srv_add_client()`                     |
|           |                              | 2. Other operations                             |
|           |                              | 3. `dhcpv4c_srv_stop()`                           |

#### State-Dependent Behavior

| Component | States                                      | Impact on Methods                                                                                     |
| --------- | ------------------------------------------- | ----------------------------------------------------------------------------------------------------- |
| Client    | INIT, SELECTING, BOUND, RENEWING, etc.     | Many functions are only valid in specific states (e.g., `dhcp4c_renew()` requires `BOUND` state).     |
| Server    | RUNNING, STOPPED                            | Client management functions likely require the `RUNNING` state.                                        |

## Sequence Diagram

```mermaid
sequenceDiagram
participant Client Module
participant DHCPV4C HAL
participant Vendor Software
participant Opensource Software
Client Module->>DHCPV4C HAL: dhcpv4c_get_ert_lease_time()
DHCPV4C HAL->>Opensource Software: UDHCPEnable_v2 is true
Opensource Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Vendor Software: UDHCPEnable_v2 is false
Vendor Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Client Module: return

Client Module->>DHCPV4C HAL: dhcpv4c_get_ert_remain_lease_time()
DHCPV4C HAL->>Opensource Software: UDHCPEnable_v2 is true
Opensource Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Vendor Software: UDHCPEnable_v2 is false
Vendor Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Client Module: return

Client Module->>DHCPV4C HAL: dhcpv4c_get_ert_ifname()
DHCPV4C HAL->>Opensource Software: UDHCPEnable_v2 is true
Opensource Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Vendor Software: UDHCPEnable_v2 is false
Vendor Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Client Module: return

Client Module->>DHCPV4C HAL: dhcpv4c_get_ert_ip_addr()
DHCPV4C HAL->>Opensource Software: UDHCPEnable_v2 is true
Opensource Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Vendor Software: UDHCPEnable_v2 is false
Vendor Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Client Module: return

Client Module->>DHCPV4C HAL: dhcpv4c_get_ert_dns_svrs()
DHCPV4C HAL->>Opensource Software: UDHCPEnable_v2 is true
Opensource Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Vendor Software: UDHCPEnable_v2 is false
Vendor Software->>DHCPV4C HAL: 
DHCPV4C HAL->>Client Module: return
````
