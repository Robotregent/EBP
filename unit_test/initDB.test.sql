GRANT USAGE ON *.* TO 'ebp_test_root'@'localhost'; /* workaround for missing "DROP USER IF EXISTS" */
DROP USER 'ebp_test_root'@'localhost';
CREATE USER 'ebp_test_root'@'localhost' IDENTIFIED BY 'ebp_test_root';
GRANT ALL PRIVILEGES ON ebp_test.* TO 'ebp_test_root'@'localhost' WITH GRANT OPTION;
GRANT CREATE USER,RELOAD,PROCESS ON *.* TO 'ebp_test_root'@'localhost' WITH GRANT OPTION;

GRANT USAGE ON *.* TO 'ebp_test_user_0'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_1'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_2'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_3'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_4'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_5'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_6'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_7'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_8'@'localhost';
GRANT USAGE ON *.* TO 'ebp_test_user_9'@'localhost';
DROP USER 'ebp_test_user_0'@'localhost';
DROP USER 'ebp_test_user_1'@'localhost';
DROP USER 'ebp_test_user_2'@'localhost';
DROP USER 'ebp_test_user_3'@'localhost';
DROP USER 'ebp_test_user_4'@'localhost';
DROP USER 'ebp_test_user_5'@'localhost';
DROP USER 'ebp_test_user_6'@'localhost';
DROP USER 'ebp_test_user_7'@'localhost';
DROP USER 'ebp_test_user_8'@'localhost';
DROP USER 'ebp_test_user_9'@'localhost';

GRANT USAGE ON *.* TO 'ebp_test_user_0'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_1'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_2'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_3'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_4'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_5'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_6'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_7'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_8'@'%';
GRANT USAGE ON *.* TO 'ebp_test_user_9'@'%';
DROP USER 'ebp_test_user_0'@'%';
DROP USER 'ebp_test_user_1'@'%';
DROP USER 'ebp_test_user_2'@'%';
DROP USER 'ebp_test_user_3'@'%';
DROP USER 'ebp_test_user_4'@'%';
DROP USER 'ebp_test_user_5'@'%';
DROP USER 'ebp_test_user_6'@'%';
DROP USER 'ebp_test_user_7'@'%';
DROP USER 'ebp_test_user_8'@'%';
DROP USER 'ebp_test_user_9'@'%';

FLUSH PRIVILEGES;
