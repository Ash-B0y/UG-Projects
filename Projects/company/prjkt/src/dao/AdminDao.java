package dao;

import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;

import resources.HibernateUtility;
import bean.User;

import com.google.gson.Gson;

import entity.SessionEntity;
import entity.UserEntity;

public class AdminDao {

	public String addNewUserDao(User user) throws Exception {

		String userName = null;
		SessionFactory sessionFactory = null;
		Session session = null;
		UserEntity newUser = new UserEntity();
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			newUser.setAddress(user.getAddress());

			newUser.setContactNo(user.getContactNo());
			newUser.setEmailId(user.getEmailId());
			newUser.setMac(user.getMac());
			newUser.setRole(user.getRole());
			newUser.setPackages(user.getPackages());
			newUser.setPassword(user.getPassword());
			newUser.setUserName(user.getUserName());
			newUser.setFullName(user.getFullName());
			session.getTransaction().begin();
			session.persist(newUser);
			session.getTransaction().commit();
			userName = user.getUserName();
		} catch (HibernateException exception) {
			exception.printStackTrace();
			throw new Exception("USERDAO.SERVER_ERROR");

		} catch (Exception exception) {
			throw new Exception("USERDAO.SERVER_ERROR");
			// DOMConfigurator.configure("src/resources/log4j.xml");

		} finally {
			if (session.isOpen() || session != null) {
				session.close();
			}
		}
		if (userName == null) {
			throw new Exception("ADMINDAO.USER_ADDED_FAILURE");

		}
		return "User successfully added with the name " + userName;
	}

	public String fetchUser()throws Exception {
		SessionFactory sessionFactory = HibernateUtility.createSessionFactory();
		Session session = null;
		String jsonUserList = null;
		List <UserEntity> allUserEntity = new LinkedList<UserEntity>();
		List <User> allUserBean = new LinkedList<User>();
		User user = null;
		String hql = "from UserEntity ue where ue.role='C'";

		try {
			session = sessionFactory.openSession();
			Query query = session.createQuery(hql);
			allUserEntity = query.list();
			if(!allUserEntity.isEmpty()){
			for (UserEntity userEntity : allUserEntity) {
				user = new User();
				user.setAddress(userEntity.getAddress());
				user.setContactNo(userEntity.getContactNo());
				user.setEmailId(userEntity.getEmailId());
				user.setFullName(userEntity.getFullName());
				user.setMac(userEntity.getMac());
				user.setPackages(userEntity.getPackages());
				allUserBean.add(user);
			}
			Gson gson = new Gson();
			jsonUserList = gson.toJson(allUserBean);
			System.out.println(jsonUserList);
			}
			else{
				throw new Exception("ADMIN.USER_EMPTY");
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
		return jsonUserList;
	}

	public void sessionUploadDao( bean.Session sessionBean) {

		SessionFactory sessionFactory = null;
		Session session = null;
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			session.getTransaction().begin();
			SessionEntity entity = new SessionEntity();

			entity.setDownload(sessionBean.getDownload());
			entity.setUpload(sessionBean.getUpload());
			entity.setTotal(sessionBean.getTotal());
			entity.setMac(sessionBean.getMac());
			entity.setIp(sessionBean.getIp());
			entity.setStartDate(sessionBean.getStartDate());
			entity.setEndDate(sessionBean.getEndDate());
			entity.setSessionDate(sessionBean.getSessionDate());
			session.persist(entity);
			session.getTransaction().commit();
			System.out.println("success");
		}

		catch (HibernateException exception) {
			exception.printStackTrace();

		} catch (Exception exception) {
			exception.printStackTrace();
			// DOMConfigurator.configure("src/resources/log4j.xml");

		} finally {
			if (session.isOpen() || session != null) {
				session.close();
			}
		}
	}
	
	// Updating User Details	
	public String updateUserDetails(User user) throws Exception {
        String userName = user.getUserName();
		SessionFactory sessionFactory = null;
		Session session = null;
		UserEntity newUser = new UserEntity();	
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			newUser=(UserEntity)session.get(UserEntity.class,user.getMac());
			newUser.setFullName(user.getFullName());
			newUser.setAddress(user.getAddress());
			newUser.setEmailId(user.getEmailId());
			newUser.setContactNo(user.getContactNo());
			
			session.getTransaction().begin();
			session.update(newUser);
			session.getTransaction().commit();
			userName = user.getUserName();
		} catch (HibernateException exception) {
			exception.printStackTrace();
			throw new Exception("USERDAO.SERVER_ERROR");

		} catch (Exception exception) {
			throw new Exception("USERDAO.SERVER_ERROR");

		} finally {
			if (session.isOpen() || session != null) 
				session.close();
		}
		return "User successfully updated";
	}	

}
