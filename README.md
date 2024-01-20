# LibreERP

LibreERP (short for Libre Enterprise Resource Planning) is a free (both of charge and as in freedom) alternative to existing ERP systems like ERPNext, Comarch ERP System, Symfonia, etc. It also aims to provide better user experience than Apache OfBiz and to be easilier extendable.

It is not only for big enterprises, but also the smallest ones and even charities and associations.

# Officially available modules:
- [] core (workers + roles, customers, other contrahents, contacts, addresses, login + register, module management) (Shipped with the official distribution)
- [] static_webpages (templated static HTML pages)
- [] market (orders, contracts, invoices, products & services + categories)
- [] store (new + bestselling, searching, ordering (customer) + order tracking (employee), asking for quotes, reclamations, reservations, availability notifications)
- ...

# Design
        database engines
             \  | /
              SOCI
                |
               sql      ,----- Lua
                |      /   ,-- Python
               db----scr--(--- other scripting languages
              / |   /  \   `-- Ruby
             /  |  /    `----- PHP
            /  mod
         srv--'
        / | \
       servers