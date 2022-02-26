package resources;

import org.apache.log4j.Logger;

import service.BillingService;
import dao.AdminDao;
import dao.BillDao;
import dao.UserDao;




public class Factory {

	public static BillingService createBillingService() {
		Logger logger = Logger.getLogger(Factory.class);
		logger.info("FactoryService: Inside BillingService Method");
		return new BillingService();
	}

	public static AdminDao createAdminDao() {
		Logger logger = Logger.getLogger(Factory.class);
		logger.info("FactoryDAO: Inside AdminDao Method");
		return new AdminDao();
	}
	public static UserDao createUserDao() {
		Logger logger = Logger.getLogger(Factory.class);
		logger.info("FactoryDAO: Inside AdminDao Method");
		return new UserDao();
	}
	public static BillDao createBillDao(){
		Logger logger = Logger.getLogger(Factory.class);
		logger.info("FactoryDAO: Inside BillDao Method");
		return new BillDao();
	}
}
