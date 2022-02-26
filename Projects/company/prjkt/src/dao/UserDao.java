package dao;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import resources.HibernateUtility;
import bean.Package;
import bean.User;

import com.google.gson.Gson;

import entity.PackageEntity;
import entity.SessionEntity;
import entity.UserEntity;

public class UserDao {

	public String checkUser(User user) throws Exception {
		SessionFactory sessionFactory = null;
		Session session = null;
		String hql = "select password from UserEntity ue where ue.userName=:userName";
		String returnRole = null;
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			Query query = session.createQuery(hql);
			query.setParameter("userName", user.getUserName());
			String returnPassword = (String) query.uniqueResult();
			if (returnPassword.equals(user.getPassword())) {
				System.out.println("inside if");
				String hql2 = "select role from UserEntity ue where ue.userName=:userName";
				Query query2 = session.createQuery(hql2);
				query2.setParameter("userName", user.getUserName());
				System.out.println("query successful");
				returnRole = (String) query2.uniqueResult();
				System.out.println(returnRole);
			} else {

				throw new Exception();
			}

		} catch (HibernateException exception) {
			System.out.println("error in query");
			exception.printStackTrace();
			throw new Exception("USERDAO.SERVER_ERROR");

		} catch (Exception exception) {
			exception.printStackTrace();
			System.out.println("normal error");
			throw new Exception("USERDAO.INVALID_USER");
			// DOMConfigurator.configure("src/resources/log4j.xml");

		} finally {
			if (session.isOpen() || session != null) {
				session.close();
			}
		}
		return returnRole;
	}

	

	// method to fetch the user details input is userName output is userEntity
	// object.
	public UserEntity DisplayDetails(String userName) throws Exception {
		SessionFactory sessionFactory = null;
		Session session = null;
		UserEntity userEntity = null;
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			session.getTransaction().begin();
			String hql = "select mac from UserEntity where userName= :username";
			Query query = session.createQuery(hql);
			query.setParameter("username", userName);
			Object mac = query.uniqueResult();
			// System.out.println(mac);
			userEntity = (UserEntity) session.get(UserEntity.class,
					(String) mac);
			System.out.println(userEntity.getMac());
		} catch (Exception exception) {
			exception.printStackTrace();
			throw new Exception("USERDAO.ERROR");

		} finally {
			if (session.isOpen() || session != null) {
				session.close();
			}
		}
		return userEntity;
	}

	// method to get the datails of the session for the particular user.
	@SuppressWarnings("unchecked")
	public String UserSessionDetails(String userName) throws Exception {
		SessionFactory sessionFactory = null;
		Session session = null;
		List<Object[]> userSessions = null;
		List<bean.Session> sessionList = new LinkedList<>();
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			session.getTransaction().begin();
			String hql = "select mac from UserEntity where userName= :username";
			Query query = session.createQuery(hql);
			query.setParameter("username", userName);
			Object mac = query.uniqueResult();
			hql = "select se.sessionDate,sum(total) from SessionEntity se where se.mac= :mac group by se.sessionDate order by se.sessionDate";
			query = session.createQuery(hql);
			query.setParameter("mac", mac);
			userSessions = query.list();

			for (int i = 0; i < userSessions.size(); i++) {
				bean.Session beanSession = new bean.Session();
				Date date = (Date) userSessions.get(i)[0];
				beanSession.setSessionDate(date);
				beanSession.setTotal((Double) userSessions.get(i)[1]);
				sessionList.add(beanSession);
			}

		} catch (Exception exception) {

			// throw new Exception("USERDAO.DATAERROR");

		} finally {
			if (session.isOpen() || session != null) {
				session.close();
			}
		}

		Gson gson = new Gson();
		String jsonUserList = gson.toJson(sessionList);
		System.out.println(jsonUserList);
		return jsonUserList;
	}

	// method to fetch the user details input is userName output is user object.
	public User fetchUserDetails(String userName) throws Exception {
		SessionFactory sessionFactory = null;
		Session session = null;
		User user = null;
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			// session.getTransaction().begin();
			String hql = "Select mac from UserEntity where userName=:userName";
			Query query = session.createQuery(hql);
			query.setParameter("userName", userName);
			Object mac = query.uniqueResult();
			UserEntity userEntity = (UserEntity) session.get(UserEntity.class,
					(String) mac);
			if (userEntity != null) {
				user = new User();
				user.setMac(userEntity.getMac());
				user.setUserName(userEntity.getUserName());
				user.setFullName(userEntity.getFullName());
				user.setPassword(userEntity.getPassword());
				user.setContactNo(userEntity.getContactNo());
				user.setAddress(userEntity.getAddress());
				user.setEmailId(userEntity.getEmailId());
				user.setRole(userEntity.getRole());
				user.setPackages(userEntity.getPackages());
			}

		} catch (HibernateException exception) {
			throw new Exception("USERDAO.SERVER_ERROR");
		}
		catch (Exception exception) {
			throw new Exception("USERDAO.INVALID_USERNAME");
		} finally {
			if (session.isOpen() || session != null)
				session.close();
		}

		return user;
	}
	
	// fetching plan details based on plan
		public Package fetchPlanDetails(String planName) throws Exception {
			SessionFactory sessionFactory = null;
			Session session = null;
			bean.Package plan = null;
			try {
				sessionFactory = HibernateUtility.createSessionFactory();
				session = sessionFactory.openSession();
				PackageEntity packageEntity = (PackageEntity) session.get(PackageEntity.class,
						planName);
				if (packageEntity != null) {
					plan = new Package();
					plan.setPackages(packageEntity.getPackages());
					plan.setDataInGB(packageEntity.getDataInGB());
					plan.setMonthlyCharges(packageEntity.getMonthlyCharges());
					plan.setChargesAfterLimit(packageEntity.getChargesAfterLimit());
				}

			} catch (HibernateException exception) {
				throw new Exception("USERDAO.SERVER_ERROR");
			} 
			catch (Exception exception) {
				throw new Exception("USERDAO.INVALID_PLAN");
			}
			finally {
				if (session.isOpen() || session != null)
					session.close();
			}

			return plan;
		}
		
		//fetching session Details based on MAC of a month 
		public List<bean.Session> fetchMonthlySessionInformation(String mac) throws Exception {
			SessionFactory sessionFactory = HibernateUtility.createSessionFactory();
			Session session = null;
			//bean.Session bb = new  bean.Session();
			String jsonUsageList = null;
			List <SessionEntity> allSessionInfoEntity = new LinkedList<SessionEntity>();
			List <bean.Session> allSessionBean = new LinkedList<bean.Session>();
			bean.Session sessionInfo =null;
		    try {
				sessionFactory = HibernateUtility.createSessionFactory();
				session = sessionFactory.openSession();
				String hql = "from SessionEntity where mac=:mac and sessionDate between :startDate and :endDate";
				Query query = session.createQuery(hql);
				query.setParameter("mac", mac);
				Date startDate = new Date();	
				Date endDate = new Date();	
				startDate = new SimpleDateFormat("dd-MM-yyyy").parse("26-06-2018");
				endDate = new SimpleDateFormat("dd-MM-yyyy").parse("26-08-2018");
	        	query.setParameter("startDate", startDate);
				query.setParameter("endDate", endDate);
				
				
				allSessionInfoEntity = query.list();
				if(!allSessionInfoEntity.isEmpty()){
				for (SessionEntity sessionInfoEntity : allSessionInfoEntity) {
					sessionInfo = new bean.Session();
					sessionInfo.setMac(sessionInfoEntity.getMac());
					sessionInfo.setIp(sessionInfoEntity.getIp());
					sessionInfo.setUpload(sessionInfoEntity.getUpload());
					sessionInfo.setDownload(sessionInfoEntity.getDownload());
					sessionInfo.setTotal(sessionInfoEntity.getUpload()+sessionInfoEntity.getDownload());
					sessionInfo.setStartDate(sessionInfoEntity.getStartDate());
					sessionInfo.setEndDate(sessionInfoEntity.getEndDate());
					sessionInfo.setSessionDate(sessionInfoEntity.getSessionDate());
					allSessionBean.add(sessionInfo);
				}
				}
				else{
					throw new Exception("ADMIN.SESSION_EMPTY");
				}
				
				
			} catch (HibernateException exception) {
				exception.printStackTrace();
				throw new Exception("USERDAO.SERVER_ERROR");

			} catch (Exception exception) {
				exception.printStackTrace();
				throw exception;
				// DOMConfigurator.configure("src/resources/log4j.xml");

			} finally {
				if (session.isOpen() || session != null) {
					session.close();
				}
			}
			return allSessionBean;
		}
}
