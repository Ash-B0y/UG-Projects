package api;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

import resources.AppConfig;
import resources.Factory;
import resources.JSONParser;
import service.BillingService;
import bean.User;
import dao.AdminDao;
import dao.UserDao;
import entity.UserEntity;



@Path("Mediation")
public class MediationBillingAPI {
	
	@Path("authentication")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	public Response auth(String dataReceived) throws Exception {

		Response response = null;
        String string = dataReceived;
        try {
            // Converting JSON into Bean
            User user = JSONParser.fromJson(string,User.class);
            UserDao userDao = Factory.createUserDao();
            String data = userDao.checkUser(user);
            String message = "{\"role\":\"" + data + "\"}";
            response = Response.status(Status.OK).entity(message).build();
        }
            catch(Exception e){
        		String message=AppConfig.PROPERTIES.getProperty(e.getMessage());
        		System.out.println("in catch block");
        		System.out.println(message);
        		String error = "{\"role\":\"" + message + "\"}";
                response = Response.status(Status.BAD_REQUEST).entity(error).build();
        	}

		
		
		return response;
	}

	@Path("adduser")
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	public Response addUser(String dataReceived) throws Exception{
		
	    Response response = null;
	    System.out.println(dataReceived);
	    try{
	    	
	    User user = (User) JSONParser.fromJson(dataReceived, User.class);
	    System.out.println(user.getContactNo()+"<-------");
	    BillingService service = Factory.createBillingService();        
	    String message = service.addUser(user);
	    System.out.println(message);
	    String error = "{\"message\":\"" + message + "\"}";
	    response = Response.status(Status.OK).entity(error).build();
	
	    }
	    catch (Exception e){
	                    
	    String message=AppConfig.PROPERTIES.getProperty(e.getMessage());
	    System.out.println(" adduser in catch block");
	    System.out.println(message);
	    String error = "{\"message\":\"" + message + "\"}";
	    response = Response.status(Status.BAD_REQUEST).entity(error).build();                                                                    
	    }  
	    return response;
	    
	    
	}
	
	@Path("getAllUser")
	@GET
	@Produces(MediaType.APPLICATION_JSON)
	public Response fetchAllUsers() {
		Response response = null;
		try {
			BillingService service = Factory.createBillingService();
			String data = service.FetchAvailableUsers();
			response = Response.status(Status.OK).entity(data).build();
		} catch (Exception e) {
			String returnString = "{\"message\":\""
					+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
			response = Response.status(Status.SERVICE_UNAVAILABLE)
					.entity(returnString).build();
		}
		return response;


	}
	
	
	
	
	@Path("getAllUserData")
	@GET
	@Produces(MediaType.APPLICATION_JSON)
	public Response getAllSession() {
		Response response = null;
		try {
			BillingService service = Factory.createBillingService();
			String data = service.FetchUserData();
			response = Response.status(Status.OK).entity(data).build();
		} catch (Exception e) {
			String returnString = "{\"message\":\""
					+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
			response = Response.status(Status.SERVICE_UNAVAILABLE)
					.entity(returnString).build();
		}
		return response;


	}


@Path("displayUserDetails")
@POST
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON)
public Response UserDetails(String userName) throws Exception{
	Response response=null;
	String returnString;
	try {
		User user = JSONParser.fromJson(userName,User.class);
        UserDao userDao = Factory.createUserDao();
        UserEntity userEntity = userDao.DisplayDetails(user.getUserName());
        returnString=JSONParser.toJson(userEntity);
        System.out.println(returnString);
        response = Response.status(Status.OK).entity(returnString).build();
    }
        catch(Exception e){
        	e.printStackTrace();
        	returnString = "{\"message\":\""
					+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
			response = Response.status(Status.SERVICE_UNAVAILABLE)
					.entity(returnString).build();
    	}
	return response;
}


@Path("getallUserSessions")
@POST

@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON)

public Response DisplaySessions(String userName) throws Exception{
	Response response = null;
	String returnString;
	try {
		User user = JSONParser.fromJson(userName,User.class);
        UserDao userDao = Factory.createUserDao();
        returnString=userDao.UserSessionDetails(user.getUserName());
        System.out.println(returnString);
        response = Response.status(Status.OK).entity(returnString).build();
    }
        catch(Exception e){
        	e.printStackTrace();
        	e.printStackTrace();
        	returnString = "{\"message\":\""
					+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
			response = Response.status(Status.SERVICE_UNAVAILABLE)
					.entity(returnString).build();
    	}
	return response;
}


@Path("generateUserBillTable")
@POST
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON)
public Response userBillGenerator(String dataReceived) throws Exception{
	String returnString = null;
	Response response = null;
	User user = JSONParser.fromJson(dataReceived,User.class);
	try{
	BillingService service = Factory.createBillingService();
	returnString=service.generatingMonthlyBill(user.getUserName());
	response = Response.status(Status.OK).entity(returnString).build();
	System.out.println(returnString);
	}

    catch(Exception e){
    	e.printStackTrace();
    	e.printStackTrace();
    	returnString = "{\"message\":\""
				+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
		response = Response.status(Status.SERVICE_UNAVAILABLE)
				.entity(returnString).build();
	}
	return response;
}

@Path("userUpdate")
@POST
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON)
public Response userUpdate(String dataReceived) throws Exception{
	String returnString = null;
	Response response = null;
	User user = JSONParser.fromJson(dataReceived,User.class);
	System.out.println(dataReceived);
	try{
	AdminDao admin = Factory.createAdminDao();
	String returnMsg =admin.updateUserDetails(user);
	returnString = "{\"message\":\""
			+ returnMsg + "\"}";
	response = Response.status(Status.OK).entity(returnString).build();
	System.out.println(returnString);
	}

    catch(Exception e){
    	e.printStackTrace();
    	e.printStackTrace();
    	returnString = "{\"message\":\""
				+ AppConfig.PROPERTIES.getProperty(e.getMessage()) + "\"}";
		response = Response.status(Status.SERVICE_UNAVAILABLE)
				.entity(returnString).build();
	}
	return response;
}

}

