import Family


# method to add children
def add_child(mother, name, gender):
    if mother in Family.Family.family_members.keys():
        if Family.Family.family_members[mother].get_name() == mother and Family.Family.family_members[mother].get_gender() == "Female" and Family.Family.family_members[mother].get_spouse():
            temp_mother = Family.Family.family_members[mother]
            name = Family.Family(name, gender, temp_mother.get_spouse(), temp_mother)

            if temp_mother.get_children():
                name_siblings = name.set_siblings(temp_mother.get_children()[:])
                del name_siblings
                for children in temp_mother.get_children():
                    if children.get_siblings():
                        children.get_siblings().append(name)
                    else:
                        children_siblings = children.set_siblings([name])
                        del children_siblings
                temp_mother.get_children().append(name)
                temp_mother_spouse_children = temp_mother.get_spouse().set_children(temp_mother.get_children())
                del temp_mother_spouse_children
            return "CHILD_ADDITION_SUCCEEDED"
        else:
            return "CHILD_ADDITION_FAILED"
    else:
        return "PERSON_NOT_FOUND"


# method to compute relation-ships
def get_relationship(name, relationship):
    if name in Family.Family.family_members.keys():
        temp_member = Family.Family.family_members[name]
        try:
            result = {'Son': temp_member.get_son, 'Daughter': temp_member.get_daughter, 'Siblings': temp_member.fetch_siblings, 'Brother-In-Law': temp_member.get_brother_in_law, 'Sister-In-Law': temp_member.get_sister_in_law, 'Paternal-Aunt': temp_member.get_paternal_aunt, 'Paternal-Uncle': temp_member.get_paternal_uncle, 'Maternal-Aunt': temp_member.get_maternal_aunt, 'Maternal-Uncle': temp_member.get_maternal_uncle}[relationship]()
            return result
        except KeyError:
            return "RELATION_SHIP_CANNOT_BE_COMPUTED"
    else:
        return "PERSON_NOT_FOUND"




