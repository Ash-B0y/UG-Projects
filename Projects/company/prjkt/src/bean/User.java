package bean;

import java.util.Date;

public class User {
	
	private String mac;
	private String userName;
	private String fullName;
	private String password;
	private String contactNo;
	private String address;
	private String role;
	private String emailId;	
	private String packages;
	private int totalDataUsed;
	public String getMac() {
		return mac;
	}
	public void setMac(String mac) {
		this.mac = mac;
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getFullName() {
		return fullName;
	}
	public void setFullName(String fullName) {
		this.fullName = fullName;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getContactNo() {
		return contactNo;
	}
	public String getRole() {
		return role;
	}
	
	public void setRole(String role) {
		this.role = role;
	}
	public void setContactNo(String contactno) {
		this.contactNo = contactno;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String location) {
		this.address = location;
	}
	public String getEmailId() {
		return emailId;
	}
	public void setEmailId(String emailid) {
		this.emailId = emailid;
	}
	public String getPackages() {
		return packages;
	}
	public void setPackages(String packages) {
		this.packages = packages;
	}
	public int getTotalDataUsed() {
		return totalDataUsed;
	}
	public void setTotalDataUsed(int totalDataUsed) {
		this.totalDataUsed = totalDataUsed;
	}
	
	
}
