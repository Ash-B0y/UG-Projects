
class RelationShip:
    # computing defined relation ships
    def get_paternal_aunt(self):
        ctr = 0
        result = ""
        if self.get_father():
            if self.get_father().get_siblings():
                for aunt in self.get_father().get_siblings():
                    if aunt.get_gender() == "Female":
                        result += aunt.get_name() + "\n"
                        ctr += 1
                if not ctr:
                    return "NONE"

            else:
                return "NONE"
        else:
            return "NONE"
        return result.strip()
            
    def get_paternal_uncle(self):
        ctr = 0
        result = ""
        if self.get_father():
            if self.get_father().get_siblings():
                for uncle in self.get_father().get_siblings():
                    if uncle.get_gender() == "Male":
                        result += uncle.get_name() + "\n"
                        ctr += 1
                if not ctr:
                    return "NONE"
            else:
                return "NONE"
        else:
            return "NONE"
               
        return result.strip()

    def get_maternal_aunt(self):
        ctr = 0
        result = ""
        if self.get_mother():
            if self.get_mother().get_siblings():
                for aunt in self.get_mother().get_siblings():
                    if aunt.get_gender() == "Female":
                        result += aunt.get_name() + "\n"
                        ctr += 1
                if not ctr:
                    return "NONE"
            else:
                return "NONE"
        else:
            return "NONE"
        return result.strip()

    def get_maternal_uncle(self):
        ctr = 0
        result = ""
        if self.get_mother():
            if self.get_mother().get_siblings():
                for uncle in self.get_mother().get_siblings():
                    if uncle.get_gender() == "Male":
                        result += uncle.get_name() + "\n"
                        ctr += 1
                if not ctr:
                    return "NONE"
            else:
                return "NONE"
        else:
            return "NONE"
        return result.strip()

    def get_brother_in_law(self):
        ctr = 0
        result = ""
        if self.get_spouse() or self.get_siblings():
            if self.get_spouse():
                if self.get_spouse().get_siblings():
                    for brother in self.get_spouse().get_siblings():
                        if brother.get_gender() == "Male":
                            result += brother.get_name() + "\n"
                            ctr += 1

            if self.get_siblings():
                for brother in self.get_siblings():
                    if brother.get_gender() == "Female":
                        if brother.get_spouse():
                            result += brother.get_name() + "\n"
                            ctr += 1
            if not ctr:
                return "NONE"

        else:
            return "NONE"
        return result.strip()

    def get_sister_in_law(self):
        ctr = 0
        result = ""
        if self.get_spouse() or self.get_siblings():
            if self.get_spouse():
                if self.get_spouse().get_siblings():
                    for sister in self.get_spouse().get_siblings():
                        if sister.get_gender() == "Female":
                            result += sister.get_name() + "\n"
                            ctr += 1

            if self.get_siblings():
                for sister in self.get_siblings():
                    if sister.get_gender() == "Male":
                        if sister.get_spouse():
                            result += sister.get_name() + "\n"
                            ctr += 1

            if not ctr:
                return "NONE"

        else:
            return "NONE"
        return result.strip()

    def get_son(self):
        ctr = 0
        result = ""
        if self.get_children():
            for son in self.get_children():
                if son.get_gender() == "Male":
                    ctr += 1
                    result += son.get_name() + "\n"

            if not ctr:
                return "NONE"
        else:
            return "NONE"
        return result.strip()

    def get_daughter(self):
        ctr = 0
        result = ""
        if self.get_children():
            for daughter in self.get_children():
                if daughter.get_gender() == "Female":
                    ctr += 1
                    result += daughter.get_name() + "\n"
            if not ctr:
                return "NONE"
        else:
            return "NONE"
        return result.strip()

    def fetch_siblings(self):
        result = ""
        if self.get_siblings():
            for siblings in self.get_siblings():
                result += siblings.get_name() + "\n"
        else:
            return "NONE"
        return result.strip()