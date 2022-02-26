package entity;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import org.hibernate.annotations.GenericGenerator;

@Entity
@Table(name="sessiondetails")
@GenericGenerator(name="generatorName", strategy = "increment")
public class SessionEntity {
	@Id
	@GeneratedValue(generator="generatorName")
	private int sessionid;
	private String mac;
	private String ip;
	private double upload;
	private double download;
	private double total;
	private String startDate;
	private String endDate;
	@Temporal(TemporalType.DATE)
	private Date sessionDate;
	
	public int getSessionid() {
		return sessionid;
	}
	public void setSessionid(int sessionid) {
		this.sessionid = sessionid;
	}
	
	public String getMac() {
		return mac;
	}
	public void setMac(String mac) {
		this.mac = mac;
	}
	public String getIp() {
		return ip;
	}
	public void setIp(String ip) {
		this.ip = ip;
	}
	public double getUpload() {
		return upload;
	}
	public void setUpload(double upload) {
		this.upload = upload;
	}
	public double getDownload() {
		return download;
	}
	public void setDownload(double download) {
		this.download = download;
	}
	public double getTotal() {
		return total;
	}
	public void setTotal(double total) {
		this.total = total;
	}
	public String getStartDate() {
		return startDate;
	}
	public void setStartDate(String startDate) {
		this.startDate = startDate;
	}
	public String getEndDate() {
		return endDate;
	}
	public void setEndDate(String endDate) {
		this.endDate = endDate;
	}
	public Date getSessionDate() {
		return sessionDate;
	}
	public void setSessionDate(Date sessionDate) {
		this.sessionDate = sessionDate;
	}
	
	
	
}
