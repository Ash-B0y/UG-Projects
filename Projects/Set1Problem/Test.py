import unittest
import Invocation
import Initializer


class TestFamily(unittest.TestCase):

    # Tester method to check if Add child method works fine.
    def test_add_child(self):
        Initializer.Initializer.create()
        self.assertEqual(Invocation.add_child('Amba', 'Srutak', 'Male'), 'CHILD_ADDITION_SUCCEEDED')
        self.assertEqual(Invocation.add_child('Chit', 'Srutak', 'Male'), 'CHILD_ADDITION_FAILED')
        self.assertEqual(Invocation.add_child('Aswathi', 'Srutak', 'Male'), 'PERSON_NOT_FOUND')

    # Tester method to check if relation_ship_fetch method works fine
    def test_get_relation_ship(self):
        self.assertEqual(Invocation.get_relationship('Amba', 'Son'), 'Vritha'+"\n"+'Srutak')
        self.assertEqual(Invocation.get_relationship('Chit', 'Daughter'), 'Dritha'+"\n"+'Tritha')
        self.assertEqual(Invocation.get_relationship('Chit', 'Father'), 'RELATION_SHIP_CANNOT_BE_COMPUTED')
        self.assertEqual(Invocation.get_relationship('Chitra', 'Paternal-Aunt'), 'NONE')
        self.assertEqual(Invocation.get_relationship('Aras', 'Siblings'), 'Chit'+"\n"+'Ish'+"\n"+'Vich'+"\n"+'Satya')
        self.assertEqual(Invocation.get_relationship('Vyas', 'Maternal-Aunt'), 'NONE')
        self.assertEqual(Invocation.get_relationship('Srutak', 'Paternal-Aunt'), 'Satya')
        self.assertEqual(Invocation.get_relationship('Srutak', 'Spouse'), 'RELATION_SHIP_CANNOT_BE_COMPUTED')
        self.assertEqual(Invocation.get_relationship('Jnki', 'Maternal-Uncle'), 'NONE')
        self.assertEqual(Invocation.get_relationship('Jaya', 'Paternal-Uncle'), 'NONE')
        self.assertEqual(Invocation.get_relationship('Lika', 'Brother-In-Law'), 'Chit\nIsh\nAras')
        self.assertEqual(Invocation.get_relationship('Arit', 'Sister-In-Law'), 'NONE')

if __name__ == '__main__':
    unittest.main()