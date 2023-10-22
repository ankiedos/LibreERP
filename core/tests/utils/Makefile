include config.mk

build : compile link
compile :
	g++ -c core/tests/utils/glueable-string-vector.test.cpp -o $(PROJECT_ROOT)/bin/core/tests/utils-glueable-string-vector.o -I$(PROJECT_ROOT)/core -I$(PROJECT_ROOT)
	g++ -c core/tests/utils/postal-code.test.cpp -o $(PROJECT_ROOT)/bin/core/tests/utils-postal-code.o -I$(PROJECT_ROOT)/core -I$(PROJECT_ROOT)
	g++ -c core/tests/utils/e-mail.test.cpp -o $(PROJECT_ROOT)/bin/core/tests/utils-e-mail.o -I$(PROJECT_ROOT)/core -I$(PROJECT_ROOT)
	g++ -c core/tests/utils/e-mail-validator.test.cpp -o $(PROJECT_ROOT)/bin/core/tests/utils-e-mail-validator.o -I$(PROJECT_ROOT)/core -I$(PROJECT_ROOT)
link :
	g++ $(PROJECT_ROOT)/bin/core/tests/utils-glueable-string-vector.o -o $(PROJECT_ROOT)/bin/core/tests/utils-glueable-string-vector -L$(PROJECT_ROOT)/bin/core -l$(BASE_NAME)-utils
	g++ $(PROJECT_ROOT)/bin/core/tests/utils-postal-code.o -o $(PROJECT_ROOT)/bin/core/tests/utils-postal-code -L$(PROJECT_ROOT)/bin/core -l$(BASE_NAME)-utils
	g++ $(PROJECT_ROOT)/bin/core/tests/utils-e-mail.o -o $(PROJECT_ROOT)/bin/core/tests/utils-e-mail -L$(PROJECT_ROOT)/bin/core -l$(BASE_NAME)-utils
	g++ $(PROJECT_ROOT)/bin/core/tests/utils-e-mail-validator.o -o $(PROJECT_ROOT)/bin/core/tests/utils-e-mail-validator -L$(PROJECT_ROOT)/bin/core -l$(BASE_NAME)-utils

run :
	$(PROJECT_ROOT)/bin/core/tests/utils-glueable-string-vector
	$(PROJECT_ROOT)/bin/core/tests/utils-postal-code
	$(PROJECT_ROOT)/bin/core/tests/utils-e-mail
	$(PROJECT_ROOT)/bin/core/tests/utils-e-mail-validator