package entity;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.persistence.Transient;
@Entity
@Table(name="User_details")
public class UserEntity {
	@Id
	private String mac;
	private String userName;
	private String fullName;
	private String password;
	private String contactNo;
	private String address;
	private String emailId;
	private String role;
	private String packages;
	@Transient
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
	
	public String getFullName() {
		return fullName;
	}
	public void setFullName(String fullName) {
		this.fullName = fullName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getPassword() {
		return password;
	}
	
	public String getRole() {
		return role;
	}
	public void setRole(String role) {
		this.role = role;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getContactNo() {
		return contactNo;
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
