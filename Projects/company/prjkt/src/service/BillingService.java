package service;

import java.util.LinkedList;
import java.util.List;

import resources.Factory;
import bean.Bill;
import bean.Package;
import bean.Session;
import bean.User;

import com.google.gson.Gson;

import dao.AdminDao;
import dao.BillDao;
import dao.UserDao;

public class BillingService {

	public String addUser(User user) throws Exception {
		String data = null;
		AdminDao adminDao = Factory.createAdminDao();
		try {
			data = adminDao.addNewUserDao(user);

		} catch (Exception e) {
			throw e;
		}
		return data;
	}

	public String FetchAvailableUsers() throws Exception {
		AdminDao adminDao = Factory.createAdminDao();
		String data = null;
		try {
			data = adminDao.fetchUser();
		} catch (Exception e) {
			e.printStackTrace();
			throw e;
		}
		return data;

	}

	public String FetchUserData() throws Exception {
		BillDao billDao = Factory.createBillDao();
		String data = null;
		try {
			data = billDao.fetchUserUsedData();
		} catch (Exception e) {
			e.printStackTrace();
			throw e;
		}
		return data;

	}

	// Generate bill
	public String generatingMonthlyBill(String userName) {
		UserDao userDao = new UserDao();
		String jsonBill = null;
		try {
			User user = userDao.fetchUserDetails("Angelina");
			Package plan = userDao.fetchPlanDetails(user.getPackages());
			List<bean.Session> sessiondetails = userDao
					.fetchMonthlySessionInformation(user.getMac());
			double total = 0;
			double totalUpload = 0;
			double totalDownload = 0;
			double totalBillAmount = plan.getMonthlyCharges();
			double excessData = 0;
			double excessCharge = 0;
			
			for (Session s : sessiondetails) {
				total += s.getTotal();
				totalUpload += s.getUpload();
				totalDownload += s.getDownload();
			}
			
			if (total > plan.getDataInGB() * 1024) {
				excessData = total - (plan.getDataInGB() * 1024);
				totalBillAmount += excessData * plan.getChargesAfterLimit();
			}
			
			if (total > plan.getDataInGB() * 1024){
				excessCharge = (total - (plan.getDataInGB() * 1024))*plan.getChargesAfterLimit();
			}	
			Bill bill = new Bill();
			bill.setPlan(plan.getPackages());
			bill.setTotalUpload(totalUpload);
			bill.setTotalDownload(totalDownload);
			bill.setTotal(total);
			bill.setExcessData(excessData);
			bill.setTotalBillAmount(totalBillAmount);
			bill.setExcessCharge(excessCharge);
			List<Object> billObject = new LinkedList<>();
			billObject.add(sessiondetails);
			billObject.add(bill);
			Gson gson = new Gson();
			jsonBill = gson.toJson(billObject);
//			System.out.println(jsonBill);

		} catch (NullPointerException e) {
			System.out.println("plan error");
			// throw new Exception("USERDAO.INVALID_PLAN");

		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("in error");
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		return jsonBill;

	}

	
}
