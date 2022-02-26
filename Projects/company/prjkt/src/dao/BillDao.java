package dao;

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

public class BillDao {
	public String fetchUserUsedData()throws Exception {
		SessionFactory sessionFactory = HibernateUtility.createSessionFactory();
		Session session = null;
		String jsonUserList = null;
		List <User> allUserBean = new LinkedList<User>();
		List<String> allUserMac = new LinkedList<>();
		String hql = "select ue.mac from UserEntity ue where ue.role='C'";
		try {
			session = sessionFactory.openSession();
			Query query = session.createQuery(hql);
			allUserMac = query.list();
			
			for(String s:allUserMac){
				List<Double> userData = new LinkedList<Double>();
				String hql2 = "select se.total from SessionEntity se where se.mac=:mac";
				Query query2 = session.createQuery(hql2);
				query2.setString("mac", s );
				userData = query2.list();
				System.out.println(userData);
				if(!userData.isEmpty()){
					String hql3 = "select ue.userName from UserEntity ue where ue.mac=:mac";
					Query query3 = session.createQuery(hql3);
					query3.setString("mac", s );
					String name = (String)query3.uniqueResult();
					System.out.println(name);
					Double totalDataUsed = 0.0;
					for(Double l: userData){
						totalDataUsed+=l;
					}
					int totalDataUsedInInt = totalDataUsed.intValue();
					System.out.println(totalDataUsedInInt);
					User userBean = new User();
					userBean.setUserName(name);
					userBean.setTotalDataUsed(totalDataUsedInInt/1024);
					allUserBean.add(userBean);
				}				
			}

			Gson gson = new Gson();
			jsonUserList = gson.toJson(allUserBean);
			System.out.println(jsonUserList);			
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
	
//	method to fetch the user details input is userName output is userEntity object.
	public User fetchUserDetails(String userName) throws Exception{
		SessionFactory sessionFactory = null;
		Session session = null;
		User user=null;
		try {
			sessionFactory = HibernateUtility.createSessionFactory();
			session = sessionFactory.openSession();
			//session.getTransaction().begin();
			String hql="Select mac from UserEntity where userName=:userName";
			Query query=session.createQuery(hql);
			query.setParameter("userName", userName);
			 Object mac=query.uniqueResult();
					
			UserEntity u=(UserEntity) session.get(UserEntity.class, (String)mac);
			 if(u!=null){
                  user=new User();
                  user.setMac(u.getMac());
                  user.setUserName(u.getUserName());
				  user.setFullName(u.getFullName());
                  user.setPassword(u.getPassword());
                  user.setContactNo(u.getContactNo());
				  user.setAddress(u.getAddress());
				  user.setEmailId(u.getEmailId());
				  user.setRole(u.getRole());
				  user.setPackages(u.getPackages());
			 }    
            
       }catch (HibernateException exception) {			
            throw new Exception("DAO.TECHNICAL_ERROR");
       }catch (Exception exception) {			
            throw exception;
       }finally {
            if(session.isOpen()|| session!=null)
                  session.close();
            }
       
       return user;
   }
}
