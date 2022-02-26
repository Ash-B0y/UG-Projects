package dao;

import java.io.File;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import bean.Package;
import bean.User;

import com.google.gson.Gson;

import entity.SessionEntity;
import resources.HibernateUtility;
import resources.XMLParser;
import service.BillingService;

public class Checking {

	public static void main(String[] args) {
//		UserDao userDao = new UserDao();
//		BillingService service = new BillingService();
//		service.generatingMonthlyBill("Angelina");
//		try {
//			userDao.UserSessionDetails("Tony");
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		XMLParser.XmlToDbConvert();
//		try {
//			User user = userDao.fetchUserDetails("Angelina");
//			Package plan = userDao.fetchPlanDetails(user.getPackages());
//			List<bean.Session> sessiondetails = userDao.fetchMonthlySessionInformation(user.getMac());
//			for(bean.Session s : sessiondetails){
//				System.out.println(s.getStartDate());
//			}
//		} 
//		catch (NullPointerException e){
//			System.out.println("plan error");
//			throw new Exception("USERDAO.INVALID_PLAN");
//			
//
//		}
//		catch (Exception e) {
//			 TODO Auto-generated catch block
//			System.out.println("in error");
//			System.out.println(e.getMessage());
//			e.printStackTrace();
//		}
//		try {
//			userDao.UserSessionDetails("Tony");
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
		AdminDao dao = new AdminDao();
		User user = new User();
		user.setUserName("Tony");
		user.setFullName("Again Tony");
		user.setAddress("USA");
		user.setContactNo("777777");
		user.setEmailId("civ.76@fg.com");
		try {
			dao.updateUserDetails(user);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
//		}
		 }
	
		
	}
